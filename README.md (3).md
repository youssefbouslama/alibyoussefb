# Chess game
## Table of content
- Introducation
- Chessbox
- button
- Chessboard
- chesspiece
- The game
- Pawn
- King
- Queen
- knight
- Rook
## Introduction
Chess is a board game of strategic skill for two players, played on a chequered board on which each playing piece is moved according to precise rules. The object is to put the opponent's king under a direct attack from which escape is impossible ( checkmate ).![enter image description here](https://cdn.discordapp.com/attachments/937879872519405578/939924627906506813/unknown.png)

![enter image description here](https://cdn.discordapp.com/attachments/937879872519405578/939923023450996767/unknown.png)
## Chessbox
### In chessbox.cpp
- For making the square chess box 
``` cpp
setRect(0,0,100,100);

  brush.setStyle(Qt::SolidPattern);

  setZValue(-1);

  setHasChessPiece(false);

  setChessPieceColor("NONE");

  currentPiece  =  NULL;

```
 - Deselecting counter part of chess piece
```cpp
if(currentPiece  ==  game->pieceToMove  &&  currentPiece){

  

  currentPiece->mousePressEvent(event);

  return;

  }
  ```
  - If selected
  ```cpp
 if(game->pieceToMove){

  //if  same  team

  if(this->getChessPieceColor()  ==  game->pieceToMove->getSide())

  return;

  //removing  the  eaten  piece

  QList  <ChessBox  *>  movLoc  =  game->pieceToMove->moveLocation();

  //To  make  sure  the  selected  box  is  in  move  zone

  int  check  =  0;

  for(size_t  i  =  0,  n  =  movLoc.size();  i  <  n;i++)  {

  if(movLoc[i]  ==  this)  {

  check++;

  

  }

  }

  //  if  not  prsent  return

  if(check  ==  0)

  return;

  //change  the  color  back  to  normal

  game->pieceToMove->decolor();

  //make  the  first  move  false  applicable  for  pawn  only

  game->pieceToMove->firstMove  =  false;

  //this  is  to  eat  or  consume  the  enemy  present  inn  the  movable  region

  if(this->getHasChessPiece()){

  this->currentPiece->setIsPlaced(false);

  this->currentPiece->setCurrentBox(NULL);

  game->placeInDeadPlace(this->currentPiece);

  

  }

  //changing  the  new  stat  and  resetting  the  previous  left  region

  game->pieceToMove->getCurrentBox()->setHasChessPiece(false);

  game->pieceToMove->getCurrentBox()->currentPiece  =  NULL;

  game->pieceToMove->getCurrentBox()->resetOriginalColor();

  placePiece(game->pieceToMove);

  

  game->pieceToMove  =  NULL;

  //changing  turn

  game->changeTurn();

  checkForCheck();

  }
  ```
  - Selecting counter part of the chess piece
  ```cpp
 else  if(this->getHasChessPiece())

  {

  this->currentPiece->mousePressEvent(event);

  }
  ```
  ###  In chessbox.h
  - The constructor
  ```cpp
  ChessBox(QGraphicsItem  *parent=0);

  ~ChessBox();
  ```
  - public member function
  ```cpp
  void  mousePressEvent(QGraphicsSceneMouseEvent  *event);

  void  setColor(QColor  color);

  void  placePiece(ChessPiece  *piece);

  

  

  void  resetOriginalColor();

  void  setOriginalColor(QColor  value);

  

  bool  getHasChessPiece();

  void  setHasChessPiece(bool  value,ChessPiece  *piece  =  0);

  

  void  checkForCheck();

  

  QString  getChessPieceColor()  ;

  void  setChessPieceColor(QString  value);

  

  int  rowLoc;

  int  colLoc;

  

  ChessPiece  *  currentPiece;
  ```
  ## Button
  - Drawing the rectangle
  ```cpp
  setRect(0,0,200,50);

  QBrush  brush;

  brush.setStyle(Qt::SolidPattern);

  brush.setColor(Qt::black);

  setBrush(brush);
  ```
  - Drawing the text
  ```cpp
  text  =  new  QGraphicsTextItem(name,this);

  int  xPos  =  rect().width()/2  -  text->boundingRect().width()/2;

  int  yPos  =  rect().height()/2  -  text->boundingRect().height()/2;

  text->setPos(xPos,yPos);

  text->setDefaultTextColor(Qt::white);
  ```
  - Allowing respond to hover
  ```cpp
  setAcceptHoverEvents(true);
  ```
  - Changing the color of the rect
  ```cpp
    if(event){

  QBrush  brush;

  brush.setStyle(Qt::SolidPattern);

  brush.setColor(Qt::blue);

  setBrush(brush);

  }
  ```
  - Public methods(events) in button.h
  ```cpp
  void  mousePressEvent(QGraphicsSceneMouseEvent  *event);

  void  hoverEnterEvent(QGraphicsSceneHoverEvent  *event);

  void  hoverLeaveEvent(QGraphicsSceneHoverEvent  *event);

signals:

  void  clicked();
  ```
  ## Chess board
  - Drawing the chess boxes
  ```cpp
  int  SHIFT  =  100;

  for(int  i  =  0;  i  <  8;  i++)  {

  for(int  j  =  0;  j  <  8;  j++)

  {

  ChessBox  *box  =  new  ChessBox();

  game->collection[i][j]  =  box;

  box->rowLoc  =  i;

  box->colLoc  =  j;

  box->setPos(x+SHIFT*j,y+SHIFT*i);

  if((i+j)%2==0)

  box->setOriginalColor(Qt::white);

  else

  box->setOriginalColor(Qt::blue);

  game->addToScene(box);
   }
 }
 ```
 - Adding the chess pieces
 ```cpp
 for(int  i  =  0;  i  <  8;  i++)  {

  for(int  j  =  0;  j  <  8;  j++)

  {

  

  ChessBox  *box  =game->collection[i][j];

  if(i  <  2)  {

  static  int  k;

  box->placePiece(black[k]);

  game->alivePiece.append(black[k]);

  game->addToScene(black[k++]);

  }

  if(i  >  5)  {

  static  int  h;

  box->placePiece(white[h]);

  game->alivePiece.append(white[h]);

  game->addToScene(white[h++]);

  }

   }

  }
```
- Setting up white
```cpp
ChessPiece  *piece;

  for(int  i  =  0;  i  <  8;  i++)  {

  piece  =  new  Pawn("WHITE");

  white.append(piece);

  }

  piece  =  new  Rook("WHITE");

  white.append(piece);

  piece  =  new  Knight("WHITE");

  white.append(piece);

  piece  =  new  Bishop("WHITE");

  white.append(piece);

  piece  =  new  Queen("WHITE");

  white.append(piece);

  piece  =  new  King("WHITE");

  white.append(piece);

  piece  =  new  Bishop("WHITE");

  white.append(piece);

  piece  =  new  Knight("WHITE");

  white.append(piece);

  piece  =  new  Rook("WHITE");

  white.append(piece);

  

}
```
-Setting up black
```cpp
ChessPiece  *piece;

  piece  =  new  Rook("BLACK");

  black.append(piece);

  piece  =  new  Knight("BLACK");

  black.append(piece);

  piece  =  new  Bishop("BLACK");

  black.append(piece);

  piece  =  new  Queen("BLACK");

  black.append(piece);

  piece  =  new  King("BLACK");

  black.append(piece);

  piece  =  new  Bishop("BLACK");

  black.append(piece);

  piece  =  new  Knight("BLACK");

  black.append(piece);

  piece  =  new  Rook("BLACK");

  black.append(piece);

  for(int  i  =  0;  i  <  8;  i++)  {

  piece  =  new  Pawn("BLACK");

  black.append(piece);

  }

}
```
- For reset
```cpp
int  k  =  0;  int  h  =  0;

  for(int  i  =  0;  i  <  8;  i++)  {

  for(int  j  =  0;  j  <  8;  j++)

  {

  

  ChessBox  *box  =game->collection[i][j];

  box->setHasChessPiece(false);

  box->setChessPieceColor("NONE");

  box->currentPiece  =  NULL;

  if(i  <  2)  {

  

  box->placePiece(black[k]);

  black[k]->setIsPlaced(true);

  black[k]->firstMove  =  true;

  game->alivePiece.append(black[k++]);

  

  }

  if(i  >  5)  {

  

  box->placePiece(white[h]);

  white[h]->setIsPlaced(true);

  white[h]->firstMove  =  true;

  game->alivePiece.append(white[h++]);

  

  }

  

  }

  }
  ```
  - Drawing public function in chessboard
  ```cpp
  void  drawBoxes(int  x,  int  y);

  void  setUpWhite();

  void  setUpBlack();

  void  addChessPiece();

  void  reset();
  ```
  ## Chess piece
  - For deselcting the chess piece
  ```cpp
  if(this  ==  game->pieceToMove){

  game->pieceToMove->getCurrentBox()->resetOriginalColor();

  game->pieceToMove->decolor();

  game->pieceToMove  =  NULL;

  return;

  }
  ```
  - If it already consumed or not the respective color s turn
  ```cpp
  if((!getIsPlaced()  )||  (  (game->getTurn()  !=  this->getSide())&&  (!game->pieceToMove))  )

  return;
  ```
  - The selecting
  ```cpp
  if(!game->pieceToMove){

  

  game->pieceToMove  =  this;

  game->pieceToMove->getCurrentBox()->setColor(Qt::yellow);

  game->pieceToMove->moves();

  }
  ```
  - Consuming counter part of the chess box
  ```cpp
  else  if(this->getSide()  !=  game->pieceToMove->getSide()){

  this->getCurrentBox()->mousePressEvent(event);

  }
  ```
  ## The game
  - Making the scene
  ```cpp
  gameScene  =  new  QGraphicsScene();

  gameScene->setSceneRect(0,0,1400,900);
  ```
  - Making the view
  ```cpp
  setFixedSize(1400,900);

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setScene(gameScene);

  QBrush  brush;

  brush.setStyle(Qt::SolidPattern);

  brush.setColor(Qt::black);

  setBackgroundBrush(brush);

  pieceToMove  =  NULL;
  ```
  - Display turn
  ```cpp
  turnDisplay = new QGraphicsTextItem();
    turnDisplay->setPos(width()/2-100,10);
    turnDisplay->setZValue(1);
    turnDisplay->setDefaultTextColor(Qt::white);
    turnDisplay->setFont(QFont("",18));
    turnDisplay->setPlainText("Turn : WHITE");

```
 - Display check
```cpp
check = new QGraphicsTextItem();
    check->setPos(width()/2-100,860);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::white);
    check->setFont(QFont("",18));
    check->setPlainText("CHECK!");
    check->setVisible(false);
    setTurn("WHITE");
```
 -Creating the title
```cpp
QGraphicsTextItem *titleText = new QGraphicsTextItem("<Chesss With 3 s>");
    QFont titleFont("ALGERIAN" , 50);
    titleText->setFont( titleFont);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 250;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listG.append(titleText);
```
 -creating the play button
```cpp
Button * playButton = new Button("Play ");
    int pxPos = width()/2 - playButton->boundingRect().width()/2;
    int pyPos = 375;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(start()));
    addToScene(playButton);
    listG.append(playButton);
```
 - creating the quit button
```cpp
Button * quitButton = new Button("Quit");
    int qxPos = width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 470;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    addToScene(quitButton);
    drawChessBoard();
    listG.append(quitButton);

```
 ## In game.h
 -constructor
```cpp
Game(QWidget *parent = 0);
```
 - public methods
```cpp
void drawDeadHolder(int x, int y, QColor color);
    void drawChessBoard();
    void displayDeadWhite();
    void displayDeadBlack();
    void placeInDeadPlace(ChessPiece *piece);
```
 - scene related
```cpp
void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);
```
 -getters and setters
```cpp
ChessPiece *pieceToMove;

    QString getTurn() ;
    void setTurn( QString value);
    void changeTurn();



    ChessBox *collection[8][8];
    QGraphicsTextItem *check;
    QList <ChessPiece *> alivePiece;
    void displayMainMenu();

    void gameOver();
    void removeAll();
```
## Pawn

- Setting the image
```cpp
if(side == "WHITE")
        setPixmap(QPixmap(":/images/pawn1.png"));
    else
        setPixmap(QPixmap(":/images/pawn.png"));
```
 - Moves of the pawn
```cpp
{
    location.clear();

    int row = this->getCurrentBox()->rowLoc;

    int col = this->getCurrentBox()->colLoc;
    if(this->getSide() == "WHITE")  {
        if(col > 0 && row > 0 && game->collection[row-1][col-1]->getChessPieceColor() == "BLACK") {
            location.append(game->collection[row-1][col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row > 0 && game->collection[row-1][col+1]->getChessPieceColor() == "BLACK") {
            location.append(game->collection[row-1][col+1]);
            boxSetting(location.last());
        }
        if(row>0 && (!game->collection[row-1][col]->getHasChessPiece())) {
            location.append(game->collection[row-1][col]);
            boxSetting(location.last());
            if(firstMove && !game->collection[row-2][col]->getHasChessPiece()){
                location.append(game->collection[row-2][col]);
                boxSetting(location.last());
            }
        }

    }
    else{
        if(col > 0 && row < 7 && game->collection[row+1][col-1]->getChessPieceColor() == "WHITE") {//left
            location.append(game->collection[row+1][col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row <  7 && game->collection[row+1][col+1]->getChessPieceColor() == "WHITE") {//right
            location.append(game->collection[row+1][col+1]);
            boxSetting(location.last());
        }
        if(row<7 && (!game->collection[row+1][col]->getHasChessPiece())) {
            location.append(game->collection[row+1][col]);
            boxSetting(location.last());
            if(firstMove && !game->collection[row+2][col]->getHasChessPiece()){
                location.append(game->collection[row+2][col]);
                boxSetting(location.last());
            }

        }

    }

}
```
## King
 - Setting the image
```cpp
if(side == "WHITE")
        setPixmap(QPixmap(":/images/king1.png"));
    else
        setPixmap(QPixmap(":/images/king.png"));
```
 - the moves of the king
```cpp

    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();

        if(col > 0 && row > 0 && !(game->collection[row-1][col-1]->getChessPieceColor() == team)) {//up left
            location.append(game->collection[row-1][col-1]);
            game->collection[row-1][col-1]->setColor(Qt::yellow);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::yellow);
            }
        }
        if(col < 7 && row > 0 && !(game->collection[row-1][col+1]->getChessPieceColor() == team)) { // up right
            location.append(game->collection[row-1][col+1]);
            game->collection[row-1][col+1]->setColor(Qt::yellow);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::yellow);
            }
        }
        if(row>0 && !(game->collection[row-1][col]->getChessPieceColor() == team)) {//up
            location.append(game->collection[row-1][col]);
            game->collection[row-1][col]->setColor(Qt::yellow);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(row<7 && !(game->collection[row+1][col]->getChessPieceColor() == team)) {//down
            location.append(game->collection[row+1][col]);
            game->collection[row+1][col]->setColor(Qt::yellow);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::yellow);
            }
        }
        if(col>0 && !(game->collection[row][col-1]->getChessPieceColor() == team)) {// left
            location.append(game->collection[row][col-1]);
            game->collection[row][col-1]->setColor(Qt::yellow);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::yellow);
            }
        }
        if(col<7 && !(game->collection[row][col+1]->getChessPieceColor() == team)) {//right
            location.append(game->collection[row][col+1]);
            game->collection[row][col+1]->setColor(Qt::yellow);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::yellow);
            }
        }
        if(col > 0 && row < 7  && !(game->collection[row+1][col-1]->getChessPieceColor() == team)) {//down left
            location.append(game->collection[row+1][col-1]);
            game->collection[row+1][col-1]->setColor(Qt::yellow);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::yellow);
            }
        }
        if(col < 7 && row < 7 && !(game->collection[row+1][col+1]->getChessPieceColor() == team)) {//down right
            location.append(game->collection[row+1][col+1]);
            game->collection[row+1][col+1]->setColor(Qt::yellow);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::yellow);
            }
        }


            findUnSafeLocation();
```
 - Find unsafe location
```cpp
QList <ChessPiece *> pList = game->alivePiece;
    for(size_t i = 0,n = pList.size(); i < n; i++) {

        if(pList[i]->getSide() != this->getSide())
        {
            QList <ChessBox *> bList = pList[i]->moveLocation();

            for(size_t j = 0, n = bList.size(); j < n; j++) {
                Pawn *c = dynamic_cast<Pawn *> (pList[i]) ;
                if(c)
                    continue;
                for(size_t k = 0, n = location.size(); k < n; k++) {
                   if(bList[j] == location [k]) {
                       location[k]->setColor(Qt::red);
                   }
                }
            }
        }
    }
```
## Queen
 - setting the image
```cpp
if(side == "WHITE")
        setPixmap(QPixmap(":/images/queen1.png"));
    else
        setPixmap(QPixmap(":/images/queen.png"));
```
 - the queen moves
```cpp
location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();
    //For up

     for(int i = row-1,j = col; i >= 0 ; i--) {
       if(game->collection[i][j]->getChessPieceColor() == team ) {
           break;
       }
       else
       {
           location.append(game->collection[i][j]);
           if(boxSetting(location.last()))
               break;
        }
    }

     //For Down

      for(int i = row+1,j = col; i <= 7 ; i++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) {
            break;
        }
        else
        {
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())){
                break;
            }
        }
     }

      //For left

       for(int i = row,j = col-1; j >= 0 ; j--) {
         if(game->collection[i][j]->getChessPieceColor() == team ) {
             break;
         }
         else
         {
             location.append(game->collection[i][j]);
             if(boxSetting(location.last()))
                break;
         }
        }
       //For Right

        for(int i = row,j = col+1; j <= 7 ; j++)
        {
              if(game->collection[i][j]->getChessPieceColor() == team ) {
                  break;
              }
              else
              {
                  location.append(game->collection[i][j]);
                  if(boxSetting(location.last()))
                      break;
               }

       }

        //For upper Left

         for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
           if(game->collection[i][j]->getChessPieceColor() == team ) {
               break;

           }
           else
           {
               location.append(game->collection[i][j]);
               if(boxSetting(location.last()) ){
                   break;
               }
           }
        }

         //For upper right

          for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
            if(game->collection[i][j]->getChessPieceColor() == team ) {
                break;

            }
            else
            {
                location.append(game->collection[i][j]);
                if(boxSetting(location.last())){
                    break;
                }
            }
         }

          //For downward right

           for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
             if(game->collection[i][j]->getChessPieceColor() == team ) {
                 break;

             }
             else
             {
                 location.append(game->collection[i][j]);
                 if(boxSetting(location.last())){
                     break;
                 }
             }
          }

           //For downward left

            for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
              if(game->collection[i][j]->getChessPieceColor() == team ) {
                  break;

              }
              else
              {
                  location.append(game->collection[i][j]);
                  if(boxSetting(location.last())){
                      break;
                  }

              }
           }
```
## Knight
 -Setting the image
```cpp
if(side == "WHITE")
        setPixmap(QPixmap(":/images/horse1.png"));
    else
        setPixmap(QPixmap(":/images/horse.png"));
```
 - the moves of the knight
```cpp
 int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    int i ,j;
    QString team  = this->getSide();
```
 -There 8 places where the knight can move
 - for the 1st up up left
```cpp
 i = row - 2;
    j = col - 1;
    if(i >=0 && j>=0 && (game->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(game->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::yellow);
    }

```
 - for the 2nd upup right
```cpp
i = row - 2;
    j = col + 1;
    if(i >=0 && j<=7 && (game->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(game->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::yellow);
    }
```
 - for the 3rd down down
```cpp
i = row + 2;
    j = col - 1;
    if(i <= 7 && j>=0 && (game->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(game->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::yellow);
    }
```
 - for the 4th down down right
```cpp
i = row + 2;
    j = col + 1;
    if(i <=7 && j<=7 && (game->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(game->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::yellow);
    }
```
 - for the 5th left left up
```cpp
i = row - 1;
    j = col - 2;
    if(i >=0 && j>=0 && (game->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(game->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::yellow);
    }
```
 - for the 6th left left down
```cpp
i = row + 1;
    j = col - 2;
    if(i <=7 && j>=0 && (game->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(game->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::yellow);
    }
```
 - for the 7th right right up
```cpp
i = row - 1;
    j = col + 2;
    if(i >=0 && j<=7 && (game->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(game->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::yellow);
    }
```
 -and for the last right right down
```cpp
i = row + 1;
    j = col +  2;
    if(i <=7 && j<=7 && (game->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(game->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::yellow);
    }
```
## Rook
 - setting the image
```cpp
if(side == "WHITE")
        setPixmap(QPixmap(":/images/rook1.png"));
    else
        setPixmap(QPixmap(":/images/rook.png"));
```
 - the moves of the rook
```cpp
location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();
```
 - for up
```cpp
for(int i = row-1,j = col; i >= 0 ; i--) {
       if(game->collection[i][j]->getChessPieceColor() == team ) {
           break;
       }
       else
       {
           location.append(game->collection[i][j]);
           if(boxSetting(location.last()))
               break;
        }
    }
```
 - for down
```cpp
for(int i = row+1,j = col; i <= 7 ; i++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) {
            break;
        }
        else
        {
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())){
                break;
            }
        }
     }
```
 - for left
```cpp
for(int i = row,j = col-1; j >= 0 ; j--) {
         if(game->collection[i][j]->getChessPieceColor() == team ) {
             break;
         }
         else
         {
             location.append(game->collection[i][j]);
             if(boxSetting(location.last()))
                break;
         }
        }
```
 - for right
```cpp
for(int i = row,j = col+1; j <= 7 ; j++)
        {
              if(game->collection[i][j]->getChessPieceColor() == team ) {
                  break;
              }
              else
              {
                  location.append(game->collection[i][j]);
                  if(boxSetting(location.last()))
                      break;
               }

       }


}
```



 


















 





 
  
  
       
       
  
