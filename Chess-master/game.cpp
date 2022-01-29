#include "game.h"
#include "button.h"
#include <QPixmap>
#include "king.h"
#include <QDebug>
Game::Game(QWidget *parent ):QGraphicsView(parent)
{

    //Making the Scene
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0,0,1400,900);

    //Making the view
    setFixedSize(1400,900);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBackgroundBrush(brush);
    pieceToMove = NULL;

    //display turn
    turnDisplay = new QGraphicsTextItem();
    turnDisplay->setPos(width()/2-100,10);
    turnDisplay->setZValue(1);
    turnDisplay->setDefaultTextColor(Qt::white);
    turnDisplay->setFont(QFont("",18));
    turnDisplay->setPlainText("Turn : WHITE");

    //display Check
    check = new QGraphicsTextItem();
    check->setPos(width()/2-100,860);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::white);
    check->setFont(QFont("",18));
    check->setPlainText("CHECK!");
    check->setVisible(false);
    setTurn("WHITE");

}

void Game::drawChessBoard()
{
    chess = new ChessBoard();
    drawDeadHolder(0,0,Qt::yellow);
    drawDeadHolder(1100,0,Qt::yellow);
     chess->drawBoxes(width()/2-400,50);

}

void Game::displayDeadWhite()
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = whiteDead.size(); i<n; i++) {
            if(j == 4){
                k++;
                j = 0;
            }
            whiteDead[i]->setPos(40+SHIFT*j++,100+SHIFT*2*k);
    }
}

void Game::displayDeadBlack()
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = blackDead.size(); i<n; i++) {
        if(j == 4){
            k++;
            j = 0;
        }
        blackDead[i]->setPos(1140+SHIFT*j++,100+SHIFT*2*k);
    }
}

void Game::placeInDeadPlace(ChessPiece *piece)
{
    if(piece->getSide() == "WHITE") {
        whiteDead.append(piece);
        King *g = dynamic_cast <King *>(piece);
        if(g){

            check->setPlainText("The winner is BLACK");
            gameOver();
        }
        displayDeadWhite();
    }
    else{
        blackDead.append(piece);
        King *g = dynamic_cast <King *>(piece);
        if(g){

            check->setPlainText("The winner is WHITE");
            gameOver();
        }
        displayDeadBlack();
    }
    alivePiece.removeAll(piece);
}

void Game::addToScene(QGraphicsItem *item)
{
    gameScene->addItem(item);
}

void Game::removeFromScene(QGraphicsItem *item)
{
    gameScene->removeItem(item);

}

QString Game::getTurn()
{
    return turn;
}

void Game::setTurn(QString value)
{
    turn = value;
}

void Game::changeTurn()
{
    if(getTurn() == "WHITE")
        setTurn("BLACK");
    else
        setTurn("WHITE");
    turnDisplay->setPlainText("Turn : " + getTurn());
}

void Game::start()
{
    for(size_t i =0, n = listG.size(); i < n; i++)
        removeFromScene(listG[i]);

    addToScene(turnDisplay);
    QGraphicsTextItem* whitePiece = new QGraphicsTextItem();
    whitePiece->setPos(70,10);
    whitePiece->setZValue(1);
    whitePiece->setDefaultTextColor(Qt::black);
    whitePiece->setFont(QFont("",14));
    whitePiece->setPlainText("WHITE PIECE");
    addToScene(whitePiece);
    QGraphicsTextItem *blackPiece = new QGraphicsTextItem();

    blackPiece->setPos(1170,10);
    blackPiece->setZValue(1);
    blackPiece->setDefaultTextColor(Qt::black);
    blackPiece->setFont(QFont("",14));
    blackPiece->setPlainText("BLACK PIECE");
    addToScene(blackPiece);
    addToScene(check);
    chess->addChessPiece();
}

void Game::drawDeadHolder(int x, int y,QColor color)
{
    deadHolder = new QGraphicsRectItem(x,y,300,900);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    deadHolder->setBrush(brush);
    addToScene(deadHolder);
}



void Game::displayMainMenu()
{
    QGraphicsPixmapItem *p = new QGraphicsPixmapItem();
    p->setPixmap(QPixmap(":/images/king1.png"));
    p->setPos(420,80);
    addToScene(p);
    listG.append(p);

    QGraphicsPixmapItem *p1 = new QGraphicsPixmapItem();
    p1->setPixmap(QPixmap(":/images/queen.png"));
    p1->setPos(920,80);
    addToScene(p1);
    listG.append(p1);
    QGraphicsPixmapItem *p2 = new QGraphicsPixmapItem();
    p2->setPixmap(QPixmap(":/images/queen1.png"));
    p2->setPos(420,470);
    addToScene(p2);
    listG.append(p2);
    QGraphicsPixmapItem *p3 = new QGraphicsPixmapItem();
    p3->setPixmap(QPixmap(":/images/king.png"));
    p3->setPos(920,470);
    addToScene(p3);
    listG.append(p3);
    //Create the title
    QGraphicsTextItem *titleText = new QGraphicsTextItem("<Chesss With 3 s>");
    QFont titleFont("ALGERIAN" , 50);
    titleText->setFont( titleFont);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 250;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listG.append(titleText);
    //create play Button
    Button * playButton = new Button("Play ");
    int pxPos = width()/2 - playButton->boundingRect().width()/2;
    int pyPos = 375;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(start()));
    addToScene(playButton);
    listG.append(playButton);

    //Create Quit Button
    Button * quitButton = new Button("Quit");
    int qxPos = width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 470;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    addToScene(quitButton);
    drawChessBoard();
    listG.append(quitButton);
}

void Game::gameOver()
{
    //removeAll();
    setTurn("WHITE");
    alivePiece.clear();
    chess->reset();




}

void Game::removeAll(){
    QList<QGraphicsItem*> itemsList = gameScene->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=check)
          removeFromScene(itemsList[i]);
    }
}
