#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

//globals
int startingCell = 0;
int currentCell = startingCell;
int winningCell = 0;
string faceDirection;
bool trailsEnabled = false;
int cell[100];
bool visited[100] = {false};


// checks for valid moves based on current cell type
bool validMove(string s){
   if (cell[currentCell] == 0){ //wall left
       if (s == "UP" || s == "DOWN" || s == "RIGHT")
         return true;
   }
   if (cell[currentCell] == 1){  //wall up
       if (s == "LEFT" || s == "DOWN" || s == "RIGHT")
         return true;
   }
   if (cell[currentCell] == 2){  //wall right
       if (s == "LEFT" || s == "DOWN" || s == "UP")
         return true;
   }
   if (cell[currentCell] == 3){  //wall down
       if (s == "LEFT" || s == "RIGHT" || s == "UP")
         return true;
   }
   if (cell[currentCell] == 4){  //walls left up
       if (s == "DOWN" || s == "RIGHT")
         return true;
   }
   if (cell[currentCell] == 5){  //walls left right
       if (s == "DOWN" || s == "UP")
         return true;
   }
   if (cell[currentCell] == 6){  //walls left down
       if (s == "RIGHT" || s == "UP")
         return true;
   }
   if (cell[currentCell] == 7){  //walls up right
       if (s == "LEFT" || s == "DOWN")
         return true;
   }
   if (cell[currentCell] == 8){  //walls up down
       if (s == "LEFT" || s == "RIGHT")
         return true;
   }
   if (cell[currentCell] == 9){  //walls right down
       if (s == "LEFT" || s == "UP")
         return true;
   }
   if (cell[currentCell] == 10){ // walls left right up
       if (s == "DOWN")
         return true;
   }
   if (cell[currentCell] == 11){ // walls up right down
       if (s == "LEFT")
         return true;
   }
   if (cell[currentCell] == 12){ // walls right down left
       if (s == "UP")
         return true;
   }
   if (cell[currentCell] == 13){ // walls down left up
       if (s == "RIGHT")
         return true;
   }
   if (cell[currentCell] == 14){ // no walls
       if (s == "LEFT" || s == "RIGHT" || s == "UP" || s == "DOWN")
         return true;
   }
  return false; // not valid move
}

//draws player arrow depending on orientation
void drawPlayer(){

   if(faceDirection == "RIGHT"){
    glPolygonMode( GL_FRONT, GL_FILL ); 
    glColor3f( 1.0, 0.0, 0.0 ); //red  
    glBegin( GL_POLYGON ); //draw player
     glVertex2i( (currentCell % 10)*50 + 10, 500 - (currentCell / 10)*50 - 15);
     glVertex2i( (currentCell % 10)*50 + 10, 500 - (currentCell / 10)*50 - 35);
     glVertex2i( (currentCell % 10)*50 + 40, 500 - (currentCell / 10)*50 - 35);   
     glVertex2i( (currentCell % 10)*50 + 40, 500 - (currentCell / 10)*50 - 15);
    glEnd();
    glBegin( GL_TRIANGLES );
     glVertex2i( (currentCell % 10)*50 + 30, 500 - (currentCell / 10)*50 - 45);
     glVertex2i( (currentCell % 10)*50 + 45, 500 - (currentCell / 10)*50 - 25);
     glVertex2i( (currentCell % 10)*50 + 30, 500 - (currentCell / 10)*50 - 5);
    glEnd();
    glColor3f( 0.0, 0.0, 0.0 ); //black 
    glBegin( GL_LINES ); //draw player outline
     glVertex2i( (currentCell % 10)*50 + 10, 500 - (currentCell / 10)*50 - 15);
     glVertex2i( (currentCell % 10)*50 + 10, 500 - (currentCell / 10)*50 - 35);
     glVertex2i( (currentCell % 10)*50 + 10, 500 - (currentCell / 10)*50 - 35);
     glVertex2i( (currentCell % 10)*50 + 30, 500 - (currentCell / 10)*50 - 35);  
     glVertex2i( (currentCell % 10)*50 + 30, 500 - (currentCell / 10)*50 - 35); 
     glVertex2i( (currentCell % 10)*50 + 30, 500 - (currentCell / 10)*50 - 45);
     glVertex2i( (currentCell % 10)*50 + 30, 500 - (currentCell / 10)*50 - 45);
     glVertex2i( (currentCell % 10)*50 + 45, 500 - (currentCell / 10)*50 - 25);
     glVertex2i( (currentCell % 10)*50 + 45, 500 - (currentCell / 10)*50 - 25);
     glVertex2i( (currentCell % 10)*50 + 30, 500 - (currentCell / 10)*50 - 5);
     glVertex2i( (currentCell % 10)*50 + 30, 500 - (currentCell / 10)*50 - 5);
     glVertex2i( (currentCell % 10)*50 + 30, 500 - (currentCell / 10)*50 - 15);
     glVertex2i( (currentCell % 10)*50 + 30, 500 - (currentCell / 10)*50 - 15);
     glVertex2i( (currentCell % 10)*50 + 10, 500 - (currentCell / 10)*50 - 15);
    glEnd();
   }

   if(faceDirection == "LEFT"){
    glPolygonMode( GL_FRONT, GL_FILL ); 
    glColor3f( 1.0, 0.0, 0.0 ); //red  
    glBegin( GL_POLYGON ); //draw player
     glVertex2i( (currentCell % 10)*50 + 10, 500 - (currentCell / 10)*50 - 15); 
     glVertex2i( (currentCell % 10)*50 + 10, 500 - (currentCell / 10)*50 - 35);
     glVertex2i( (currentCell % 10)*50 + 40, 500 - (currentCell / 10)*50 - 35);   
     glVertex2i( (currentCell % 10)*50 + 40, 500 - (currentCell / 10)*50 - 15);
    glEnd();
    glBegin( GL_TRIANGLES );
     glVertex2i( (currentCell % 10)*50 + 20, 500 - (currentCell / 10)*50 - 45);
     glVertex2i( (currentCell % 10)*50 + 5, 500 - (currentCell / 10)*50 - 25);
     glVertex2i( (currentCell % 10)*50 + 20, 500 - (currentCell / 10)*50 - 5);
    glEnd();
    glColor3f( 0.0, 0.0, 0.0 ); //black 
    glBegin( GL_LINES ); //draw player outline
     glVertex2i( (currentCell % 10)*50 + 20, 500 - (currentCell / 10)*50 - 5);
     glVertex2i( (currentCell % 10)*50 + 5, 500 - (currentCell / 10)*50 - 25);
     glVertex2i( (currentCell % 10)*50 + 5, 500 - (currentCell / 10)*50 - 25);
     glVertex2i( (currentCell % 10)*50 + 20, 500 - (currentCell / 10)*50 - 45);
     glVertex2i( (currentCell % 10)*50 + 20, 500 - (currentCell / 10)*50 - 45);
     glVertex2i( (currentCell % 10)*50 + 20, 500 - (currentCell / 10)*50 - 35);
     glVertex2i( (currentCell % 10)*50 + 20, 500 - (currentCell / 10)*50 - 35);
     glVertex2i( (currentCell % 10)*50 + 40, 500 - (currentCell / 10)*50 - 35); 
     glVertex2i( (currentCell % 10)*50 + 40, 500 - (currentCell / 10)*50 - 35); 
     glVertex2i( (currentCell % 10)*50 + 40, 500 - (currentCell / 10)*50 - 15);
     glVertex2i( (currentCell % 10)*50 + 40, 500 - (currentCell / 10)*50 - 15);
     glVertex2i( (currentCell % 10)*50 + 20, 500 - (currentCell / 10)*50 - 15); 
     glVertex2i( (currentCell % 10)*50 + 20, 500 - (currentCell / 10)*50 - 15); 
     glVertex2i( (currentCell % 10)*50 + 20, 500 - (currentCell / 10)*50 - 5);
    glEnd();
   }

   if(faceDirection == "UP"){
    glPolygonMode( GL_FRONT, GL_FILL ); 
    glColor3f( 1.0, 0.0, 0.0 ); //red  
    glBegin( GL_POLYGON ); //draw player
     glVertex2i( (currentCell % 10)*50 + 15, 500 - (currentCell / 10)*50 - 10);
     glVertex2i( (currentCell % 10)*50 + 35, 500 - (currentCell / 10)*50 - 10);
     glVertex2i( (currentCell % 10)*50 + 35, 500 - (currentCell / 10)*50 - 40);   
     glVertex2i( (currentCell % 10)*50 + 15, 500 - (currentCell / 10)*50 - 40);
    glEnd();
    glBegin( GL_TRIANGLES );
     glVertex2i( (currentCell % 10)*50 + 45, 500 - (currentCell / 10)*50 - 20);
     glVertex2i( (currentCell % 10)*50 + 25, 500 - (currentCell / 10)*50 - 5);
     glVertex2i( (currentCell % 10)*50 + 5, 500 - (currentCell / 10)*50 - 20);
    glEnd();
    glColor3f( 0.0, 0.0, 0.0 ); //black 
    glBegin( GL_LINES ); //draw player outline
     glVertex2i( (currentCell % 10)*50 + 5, 500 - (currentCell / 10)*50 - 20);
     glVertex2i( (currentCell % 10)*50 + 25, 500 - (currentCell / 10)*50 - 5);
     glVertex2i( (currentCell % 10)*50 + 25, 500 - (currentCell / 10)*50 - 5);
     glVertex2i( (currentCell % 10)*50 + 45, 500 - (currentCell / 10)*50 - 20);
     glVertex2i( (currentCell % 10)*50 + 45, 500 - (currentCell / 10)*50 - 20);
     glVertex2i( (currentCell % 10)*50 + 35, 500 - (currentCell / 10)*50 - 20);
     glVertex2i( (currentCell % 10)*50 + 35, 500 - (currentCell / 10)*50 - 20);
     glVertex2i( (currentCell % 10)*50 + 35, 500 - (currentCell / 10)*50 - 40); 
     glVertex2i( (currentCell % 10)*50 + 35, 500 - (currentCell / 10)*50 - 40); 
     glVertex2i( (currentCell % 10)*50 + 15, 500 - (currentCell / 10)*50 - 40);
     glVertex2i( (currentCell % 10)*50 + 15, 500 - (currentCell / 10)*50 - 40);
     glVertex2i( (currentCell % 10)*50 + 15, 500 - (currentCell / 10)*50 - 20); 
     glVertex2i( (currentCell % 10)*50 + 15, 500 - (currentCell / 10)*50 - 20); 
     glVertex2i( (currentCell % 10)*50 + 5, 500 - (currentCell / 10)*50 - 20);
    glEnd();
   }

   if(faceDirection == "DOWN"){
    glPolygonMode( GL_FRONT, GL_FILL ); 
    glColor3f( 1.0, 0.0, 0.0 ); //red  
    glBegin( GL_POLYGON ); //draw player
     glVertex2i( (currentCell % 10)*50 + 15, 500 - (currentCell / 10)*50 - 10);
     glVertex2i( (currentCell % 10)*50 + 35, 500 - (currentCell / 10)*50 - 10);
     glVertex2i( (currentCell % 10)*50 + 35, 500 - (currentCell / 10)*50 - 40);   
     glVertex2i( (currentCell % 10)*50 + 15, 500 - (currentCell / 10)*50 - 40);
    glEnd();
    glBegin( GL_TRIANGLES );
     glVertex2i( (currentCell % 10)*50 + 45, 500 - (currentCell / 10)*50 - 30);
     glVertex2i( (currentCell % 10)*50 + 25, 500 - (currentCell / 10)*50 - 45);
     glVertex2i( (currentCell % 10)*50 + 5, 500 - (currentCell / 10)*50 - 30);
    glEnd();
    glColor3f( 0.0, 0.0, 0.0 ); //black 
    glBegin( GL_LINES ); //draw player outline
     glVertex2i( (currentCell % 10)*50 + 15, 500 - (currentCell / 10)*50 - 10);
     glVertex2i( (currentCell % 10)*50 + 35, 500 - (currentCell / 10)*50 - 10);
     glVertex2i( (currentCell % 10)*50 + 35, 500 - (currentCell / 10)*50 - 10);
     glVertex2i( (currentCell % 10)*50 + 35, 500 - (currentCell / 10)*50 - 30);  
     glVertex2i( (currentCell % 10)*50 + 35, 500 - (currentCell / 10)*50 - 30); 
     glVertex2i( (currentCell % 10)*50 + 45, 500 - (currentCell / 10)*50 - 30);
     glVertex2i( (currentCell % 10)*50 + 45, 500 - (currentCell / 10)*50 - 30);
     glVertex2i( (currentCell % 10)*50 + 25, 500 - (currentCell / 10)*50 - 45);
     glVertex2i( (currentCell % 10)*50 + 25, 500 - (currentCell / 10)*50 - 45);
     glVertex2i( (currentCell % 10)*50 + 5, 500 - (currentCell / 10)*50 - 30);
     glVertex2i( (currentCell % 10)*50 + 5, 500 - (currentCell / 10)*50 - 30);
     glVertex2i( (currentCell % 10)*50 + 15, 500 - (currentCell / 10)*50 - 30);
     glVertex2i( (currentCell % 10)*50 + 15, 500 - (currentCell / 10)*50 - 30);
     glVertex2i( (currentCell % 10)*50 + 15, 500 - (currentCell / 10)*50 - 10);
    glEnd();
   }
}

// sets a cell to visited
void setVisited(int n){
  visited[n] = true;
}

// check for win condition
bool checkWin(){
  if (currentCell == winningCell){
    return true;
  }
  return false;
}


// finds an open wall for faceDirection
void findDirection(){
  if ( validMove("UP") )
    faceDirection = "UP";
  else if ( validMove("DOWN") )
    faceDirection = "DOWN";
  else if ( validMove("LEFT") )
    faceDirection = "LEFT";
  else
    faceDirection = "RIGHT";
}


// draws trail of cells visited
void drawTrail(){
   glPolygonMode( GL_FRONT, GL_FILL ); 
   glColor3f( 0.0, 0.0, 1.0 ); //blue  

   for (int i = 0; i < 100; i++){
     if(visited[i] == true){
       glBegin( GL_POLYGON ); //draw trail
         glVertex2i( (i % 10)*50 + 20, 500 - (i / 10)*50 - 15);
         glVertex2i( (i % 10)*50 + 35, 500 - (i / 10)*50 - 15);
         glVertex2i( (i % 10)*50 + 35, 500 - (i / 10)*50 - 30);   
         glVertex2i( (i % 10)*50 + 20, 500 - (i / 10)*50 - 30);
       glEnd();
     }
   }
}

// toggles drawing of trails
void changeTrails(){
  if(trailsEnabled == true)
    trailsEnabled = false;
  else
    trailsEnabled = true;
}

// draws winning cell until you reach it
void drawWinningCell(){
   if(!checkWin()){
     glPolygonMode( GL_FRONT, GL_FILL ); 
     glColor3f( 0.0, 1.0, 0.0 ); //green
     glBegin( GL_LINES ); // draw "F" for "finish"
      glVertex2i( (winningCell % 10)*50 + 10, 500 - (winningCell / 10)*50 - 8);
      glVertex2i( (winningCell % 10)*50 + 10, 500 - (winningCell / 10)*50 - 45);
      glVertex2i( (winningCell % 10)*50 + 10, 500 - (winningCell / 10)*50 - 45);
      glVertex2i( (winningCell % 10)*50 + 20, 500 - (winningCell / 10)*50 - 45);
      glVertex2i( (winningCell % 10)*50 + 20, 500 - (winningCell / 10)*50 - 45);
      glVertex2i( (winningCell % 10)*50 + 20, 500 - (winningCell / 10)*50 - 35); 
      glVertex2i( (winningCell % 10)*50 + 20, 500 - (winningCell / 10)*50 - 35);
      glVertex2i( (winningCell % 10)*50 + 30, 500 - (winningCell / 10)*50 - 35);
      glVertex2i( (winningCell % 10)*50 + 30, 500 - (winningCell / 10)*50 - 35);
      glVertex2i( (winningCell % 10)*50 + 30, 500 - (winningCell / 10)*50 - 25);
      glVertex2i( (winningCell % 10)*50 + 30, 500 - (winningCell / 10)*50 - 25);
      glVertex2i( (winningCell % 10)*50 + 20, 500 - (winningCell / 10)*50 - 25);
      glVertex2i( (winningCell % 10)*50 + 20, 500 - (winningCell / 10)*50 - 25);
      glVertex2i( (winningCell % 10)*50 + 20, 500 - (winningCell / 10)*50 - 15);
      glVertex2i( (winningCell % 10)*50 + 20, 500 - (winningCell / 10)*50 - 15);
      glVertex2i( (winningCell % 10)*50 + 30, 500 - (winningCell / 10)*50 - 15);
      glVertex2i( (winningCell % 10)*50 + 30, 500 - (winningCell / 10)*50 - 15);
      glVertex2i( (winningCell % 10)*50 + 30, 500 - (winningCell / 10)*50 - 8);
      glVertex2i( (winningCell % 10)*50 + 30, 500 - (winningCell / 10)*50 - 8);
      glVertex2i( (winningCell % 10)*50 + 10, 500 - (winningCell / 10)*50 - 8);
     glEnd();
   }
}

// displays "You Win!" in various color in the middle of the screen
void drawWinScreen(){
  glColor3f( 0.0, 0.0, 0.1 );
  glPolygonMode( GL_FRONT, GL_FILL ); 
  glBegin( GL_POLYGON ); //background for "you win"
   glVertex2i(75, 325);
   glVertex2i(75, 225);
   glVertex2i(425, 225);     
   glVertex2i(425, 325);
  glEnd();

  glTranslatef(100, 250, 0);
  glScalef(0.5, 0.5, 0.5);

  glColor3f( 1.0, 0.0, 0.0 );
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Y'); // "You win!" in various colors
  glColor3f( 0.0, 1.0, 0.0 );
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
  glColor3f( 0.5, 1.0, 0.0 );
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'u');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');
  glColor3f( 0.5, 0.0, 0.5 );
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'W');
  glColor3f( 1.0, 0.5, 0.0 );
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'i');
  glColor3f( 0.0, 1.0, 0.0 );
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'n');
  glColor3f( 1.0, 0.0, 0.0 );
  glutStrokeCharacter(GLUT_STROKE_ROMAN, '!');
}

// starting settings
void init(){
   glClearColor( 1.0, 1.0, 1.0, 0.0 );	//set white background color
   glClear( GL_COLOR_BUFFER_BIT );	//clear screen
   glColor3f ( 0.0, 0.0, 0.0 );         //black
   glLineWidth( 5.0 );			//5 pixel line width
   glMatrixMode( GL_PROJECTION );       //projection matrix mode
   glLoadIdentity();			//replace current matrix with identity matrix
   gluOrtho2D( 0.0, 500.0, 0.0, 500.0 );//world window = viewport
   
   // for smoothing lines
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable( GL_LINE_SMOOTH );
}

// draws maze based on cell type codes
void drawMaze(){
for (int i = 0; i < 100; i++){
     if(cell[i] == 0){//left
       glBegin( GL_LINES );		
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //left
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );
       glEnd();
     }
     if(cell[i] == 1){//up
       glBegin( GL_LINES );		
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //up	
         glVertex2i( (i%10)*50 + 50, 500 - (i/10)*50 );	
       glEnd();
     }
     if(cell[i] == 2){//right
       glBegin( GL_LINES );		
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50) );	//right	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
       glEnd();
     }
     if(cell[i] == 3){//down
       glBegin( GL_LINES );		
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );	//down	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
       glEnd();
     }
     if(cell[i] == 4){//left, up
       glBegin( GL_LINES );
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //left
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //up	
         glVertex2i( (i%10)*50 + 50, 500 - (i/10)*50 );
       glEnd();
     }
     if(cell[i] == 5){//left, right
       glBegin( GL_LINES );
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //left
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50) );	//right	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
       glEnd();
     }
     if(cell[i] == 6){//left, down
       glBegin( GL_LINES );
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //left
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );	//down	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
       glEnd();
     }
     if(cell[i] == 7){//up, right
       glBegin( GL_LINES );
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //up	
         glVertex2i( (i%10)*50 + 50, 500 - (i/10)*50 );
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50) );	//right	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
       glEnd(); 
     }
     if(cell[i] == 8){//up, down
       glBegin( GL_LINES );
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //up	
         glVertex2i( (i%10)*50 + 50, 500 - (i/10)*50 );
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );	//down	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
       glEnd();
     }
     if(cell[i] == 9){//right, down
       glBegin( GL_LINES );
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50) );	//right	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );	//down	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
       glEnd();
     }
     if(cell[i] == 10){//left, right, up
       glBegin( GL_LINES );
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //left
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50) );	//right	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //up	
         glVertex2i( (i%10)*50 + 50, 500 - (i/10)*50 );
       glEnd();
     }
     if(cell[i] == 11){//up, right, down
       glBegin( GL_LINES );
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //up	
         glVertex2i( (i%10)*50 + 50, 500 - (i/10)*50 );
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50) );	//right	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );	//down	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
       glEnd();
     }
     if(cell[i] == 12){//right, down, left
       glBegin( GL_LINES );
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50) );	//right	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );	//down	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //left
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );
       glEnd();
     }
     if(cell[i] == 13){//down, left, up
       glBegin( GL_LINES );
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );	//down	
         glVertex2i( (i%10)*50 + 50, 500 - ((i/10)*50 + 50) );
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //left
         glVertex2i( (i%10)*50     , 500 - ((i/10)*50 + 50) );
         glVertex2i( (i%10)*50     , 500 - (i/10)*50 );	        //up	
         glVertex2i( (i%10)*50 + 50, 500 - (i/10)*50 );
       glEnd();
     }
    // cell[i] == 14 not needed as that cell type has no sides
   }
}

//displays relevant visual units
void display(){
   init();
   drawMaze();
   if (trailsEnabled == true){
     drawTrail();
   }
   drawWinningCell();
   drawPlayer();
   if (checkWin()){
     drawWinScreen();
   }
   glFlush();
}

//fill maze with celltype codes for walls, set starting/current/winning cells, and align arrow 
void fillMaze(){
  int temp[102]; // 100 maze cells + starting cell + winning cell
  ifstream myfile("MazeData.txt"); // open MazeData.txt in read-only mode
  if (myfile.fail()){
   exit(EXIT_FAILURE);  // close program if MazeData.txt can't be found/opened
  }
  int i = 0;
  int cellType = 0;
  while(!myfile.eof())  // process data file
  {
    myfile >> cellType;
    temp[i] = cellType;
    ++i;
  }
  myfile.close();       // close file

  // copy maze data from data file into cell[]
  for(int i = 0; i < 100; i++){
    cell[i] = temp[i];
  }
  // initialize startingCell from value in MazeData.txt
  startingCell = temp[100];
  // initialize currentcell with starting cell's value
  currentCell = startingCell;
  // initialize winningCell from from value in MazeData.txt
  winningCell = temp[101];
  findDirection();  // aligns arrow to open wall
}

// resets game
void restart(){
  fillMaze();                       // reload maze data (allows for on-the-fly changes to maze design)
  for (int i = 0; i < 100; i++){    // makes all cells unvisited
    visited[i] = false;
  }
}

// process keyboard input
void keyboard(unsigned char key, int x, int y)
{
     switch (key) { // ESC key in ascii to exit program
        case 27:
          exit(0);
          break;
        case 'w':  // move up if you can
          faceDirection = "UP";
          if (validMove("UP") && !checkWin()){
            setVisited(currentCell);
            currentCell -= 10;
          }
          glutPostRedisplay();
          break;
        case 'a':  // move left if you can
          faceDirection = "LEFT";
          if (validMove("LEFT") && !checkWin()){
            setVisited(currentCell);
            currentCell--;
          }
          glutPostRedisplay();
          break;
        case 's':  // move down if you can
          faceDirection = "DOWN";
          if (validMove("DOWN") && !checkWin()){
            setVisited(currentCell);
            currentCell += 10;
          }
          glutPostRedisplay();
          break;
        case 'd':  // move right if you can
          faceDirection = "RIGHT";
          if (validMove("RIGHT") && !checkWin()){
            setVisited(currentCell);
            currentCell++;
          }
          glutPostRedisplay();
          break;
        case 'r':  // restarts game
          restart();
          glutPostRedisplay();
          break;
        case 't': // enables/disables trail draws
          changeTrails();
          glutPostRedisplay();
          break;
    }
}

int main( int argc, char *argv[] )
{
   fillMaze();

   // Set things (glut) up 
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

   // Create the window and handlers 
   glutCreateWindow("A-Maze-ING!");
   glutReshapeWindow( 800, 800 );
   glutInitWindowPosition(0, 0);
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);


   //perpetual loop
   glutMainLoop();
   return(0);

}
