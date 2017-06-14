
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <avr/pgmspace.h> 

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

#define UP 12
#define DOWN 13
#define LEFT A4
#define RIGHT A5

/*
byte labyrinth[16][16] = {
              {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
              {1,4,1,0,0,0,1,0,0,0,0,0,0,0,1,1},
              {1,0,1,0,1,0,0,2,1,1,0,1,1,0,0,1},
              {1,0,1,0,1,0,1,0,0,1,0,0,1,1,0,1},
              {1,0,1,0,1,1,1,1,1,1,0,1,1,0,0,1},
              {1,0,0,0,0,0,1,0,0,2,0,0,1,0,1,1},
              {1,1,1,1,1,0,1,1,1,1,1,0,1,0,0,1},
              {1,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1},
              {1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,1},
              {1,0,0,0,0,0,0,1,1,0,1,1,1,1,0,1},
              {1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1},
              {1,0,0,0,0,0,0,0,1,1,0,1,0,1,1,1},
              {1,1,1,1,1,0,1,0,0,1,0,1,0,0,0,1},
              {1,0,0,0,1,0,1,0,1,1,1,1,0,1,0,1},
              {1,3,1,0,0,0,1,0,0,0,0,0,0,1,0,1},
              {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
             };
*/

byte labyrinth[16*16] = {
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,4,1,0,0,0,1,0,0,0,0,0,0,0,1,1,
              1,0,1,0,1,0,0,2,1,1,0,1,1,0,0,1,
              1,0,1,0,1,0,1,0,0,1,0,0,1,1,0,1,
              1,0,1,0,1,1,1,1,1,1,0,1,1,0,0,1,
              1,0,0,0,0,0,1,0,0,2,0,0,1,0,1,1,
              1,1,1,1,1,0,1,1,1,1,1,0,1,0,0,1,
              1,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1,
              1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,1,
              1,0,0,0,0,0,0,1,1,0,1,1,1,1,0,1,
              1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,
              1,0,0,0,0,0,0,0,1,1,0,1,0,1,1,1,
              1,1,1,1,1,0,1,0,0,1,0,1,0,0,0,1,
              1,0,0,0,1,0,1,0,1,1,1,1,0,1,0,1,
              1,3,1,0,0,0,1,0,0,0,0,0,0,1,0,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
             };


byte r = 50;
byte g = 80;
byte b = 20;
    uint8_t _r = 0; 
    uint8_t _g = 0;
    uint8_t _b = 0;

// boolean created = false;
byte labSize = 32;

byte playerPositionX = 1;
byte playerPositionY = 1;

int up;
int down;
int left;
int right;

bool block;

void setup() {

  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  Serial.begin(9600);
  Serial.println("drawLab:");
 matrix.begin();
  
  // draw a pixel in solid white
  drawLab((byte*) &labyrinth);
  matrix.drawPixel(0, 0, matrix.Color333(7, 7, 7)); 
  // Serial.println("drawLab:");
  /*
  
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  Serial.begin(9600);
  matrix.begin();
  
  //createLabyrinth();
  Serial.println("drawLab:");
  drawLab((byte*) &labyrinth);
  Serial.println("end - drawLab");

  //matrix.drawPixel(2,3,matrix.Color333(1,2,3));
  */
}

void loop() {
  
  up = digitalRead(UP);
  down = digitalRead(DOWN);
  left = digitalRead(LEFT);
  right = digitalRead(RIGHT);

  
  if(up == HIGH && !block){
    movePlayer(1);
    block = true;
  }
  if(down == HIGH && !block){
    movePlayer(2);
    block = true;
  }
  if(left == HIGH && !block){
    movePlayer(3);
    block = true;
  }
  if(right == HIGH && !block){
    movePlayer(4);
    block = true;
  }
  if(up==LOW && down == LOW && left == LOW && right ==LOW){
    block = false;
  }
}



void drawLab(byte *lab){
 // Serial.println("================================");
 // Serial.println("draw");
 // Serial.println("================================");

  for (int e = 0; e < 16*16; e++) {
    byte tmp = *(lab + e);
    int j = e % 16;
    int i = e / 16;
    
    if (tmp == 1) {
        _r = 5;
        _g = 5;
        _b = 5;
    }else if (tmp == 2) {
        _r = 1;
        _g = 1;
        _b = 1;
    } else {
        _r = 0;
        _g = 0;
        _b = 0;
    }

   // Serial.print(_r);
   // Serial.println();
   _r = 0; _g = 0; _b = 0;
   // Serial.print(_r);
   // Serial.println();
    
    matrix.drawPixel(i,j,matrix.Color333(_r,_g,_b));
    }
    //Serial.println();
     
   
     
}


void movePlayer(byte direction){
  clearDot(playerPositionX*2,playerPositionY*2);
  //byte temp = labyrinth[playerPositionY-1][playerPositionX];
  //Serial.println(temp);
  switch(direction){
    case 1: 
      if(/*labyrinth[playerPositionY-1][playerPositionX]!= 1*/true){
        playerPositionY-=1; 
      }
      break;
    case 2:
      if(/*labyrinth[playerPositionY+1][playerPositionX]!= 1*/true){
        playerPositionY+=1; 
      }
      break;
    case 3:
      if(/*labyrinth[playerPositionY][playerPositionX-1]!= 1*/true){
        playerPositionX-=1; 
      }
      break;
    case 4:
      if(/*labyrinth[playerPositionY][playerPositionX+1]!= 1*/true){
        playerPositionX+=1; 
      }
      break;
  }
  
  matrix.drawPixel(playerPositionX*2,playerPositionY*2,matrix.Color333(0,255,0));
  matrix.drawPixel(playerPositionX*2+1,playerPositionY*2,matrix.Color333(0,255,0));
  matrix.drawPixel(playerPositionX*2,playerPositionY*2+1,matrix.Color333(0,255,0));
  matrix.drawPixel(playerPositionX*2+1,playerPositionY*2+1,matrix.Color333(0,255,0));
}

////////////////////////
//old
////////////////////////
void createLabyrinth(){
  byte center = ((32-labSize)/2);
  for(int i=0; i<labSize;i++){
    for(int j=0; j<labSize;j++){
      if(true){ //i==0||i==(labSize-1)||j==0||j==(labSize-1)
        int moveX = i+center;
        int moveY = j+center;
        matrix.drawPixel(moveX,moveY,matrix.Color333(r,g,b));
      }
    }
  }
  matrix.drawPixel(playerPositionX*2,playerPositionY*2,matrix.Color333(0,255,0));
  matrix.drawPixel(playerPositionX*2+1,playerPositionY*2,matrix.Color333(0,255,0));
  matrix.drawPixel(playerPositionX*2,playerPositionY*2+1,matrix.Color333(0,255,0));
  matrix.drawPixel(playerPositionX*2+1,playerPositionY*2+1,matrix.Color333(0,255,0));
  //byte help= ((labSize-1)*(labSize-1));
  //byte goal = rand()%(30-50 + 1) + 50;
}

void clearDot(byte x,byte y){
   matrix.drawPixel(x,y,matrix.Color333(0,0,0));
   matrix.drawPixel(x,y+1,matrix.Color333(0,0,0));
   matrix.drawPixel(x+1,y,matrix.Color333(0,0,0));
   matrix.drawPixel(x+1,y+1,matrix.Color333(0,0,0));
}
