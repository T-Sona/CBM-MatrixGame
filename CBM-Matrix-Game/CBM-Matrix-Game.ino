
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <avr/pgmspace.h> 

#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

#define UP 52
#define DOWN 53
#define LEFT 50
#define RIGHT 51

byte labyrinth[16*16] = {
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,2,1,0,0,0,1,0,0,0,0,0,0,0,1,1,
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

byte playerPositionX = 1;
byte playerPositionY = 1;

int up;
int down;
int left;
int right;

bool block;

void setup() {

  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  Serial.begin(9600);
  Serial.println("drawLab:");
  matrix.begin();
  
  // draw a pixel in solid white
  drawLab((byte*) &labyrinth);
  matrix.drawPixel(0, 0, matrix.Color333(7, 7, 7)); 
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
    Serial.println("r");
    movePlayer(4);
    block = true;
  }
  if(up==LOW && down == LOW && left == LOW && right ==LOW){
    Serial.print("_");
    block = false;
  }
}

void draw(byte x, byte y, byte tmp ){
  x*=2;
  y*=2;
  uint8_t r = 0; 
  uint8_t g = 0;
  uint8_t b = 0;
  
      if (tmp == 1) {
        r = 68;
        g = 18;
        b = 166;
    }else if (tmp == 2) {
        r = 214;
        g = 204;
        b = 32;
    }else if (tmp == 3) {
        r = 172;
        g = 163;
        b = 14;
    } else if (tmp == 4){
        g = 250;
    }
    
  matrix.drawPixel(x,y,matrix.Color888(r,g,b));
  matrix.drawPixel(x,y+1,matrix.Color888(r,g,b));
  matrix.drawPixel(x+1,y,matrix.Color888(r,g,b));
  matrix.drawPixel(x+1,y+1,matrix.Color888(r,g,b));
}

void drawLab(byte *lab){

  for (int e = 0; e < 16*16; e++) {
    byte tmp = *(lab + e);
    int j = e % 16;
    int i = e / 16;
    draw(j,i,tmp);
  }
  
}


void movePlayer(byte direction){
  draw(playerPositionX,playerPositionY, *(labyrinth+(playerPositionX+16*playerPositionY)));
  //byte temp = labyrinth[playerPositionY-1][playerPositionX];

  byte above = *(labyrinth+(playerPositionY*16)+playerPositionX-16);
  byte below = *(labyrinth+(playerPositionY*16)+playerPositionX+16);
  byte left = *(labyrinth+(playerPositionY*16)+playerPositionX-1);
  byte right = *(labyrinth+(playerPositionY*16)+playerPositionX+1);
  Serial.print("above: ");
  Serial.println(above);
    Serial.print("below: ");
  Serial.println(below);
    Serial.print("left: ");
  Serial.println(left);
    Serial.print("right: ");
  Serial.println(right);
  
  switch(direction){
    case 1: 
      if(above != 1){
        playerPositionY-=1; 
      }
      break;
    case 2:
      if(below != 1){
        playerPositionY+=1; 
      }
      break;
    case 3:
      if(left != 1){
        playerPositionX-=1; 
      }
      break;
    case 4:
      if(right!= 1){
        playerPositionX+=1; 
      }
      break;
  }
  draw(playerPositionX,playerPositionY,4);
}
