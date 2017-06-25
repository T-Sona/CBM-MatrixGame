
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

byte labyrinth[16 * 16] = {
  1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
  1, 5, 1, 0, 0, 0, 0, 1,  1, 1, 0, 0, 0, 0, 1, 1,
  1, 0, 1, 0, 1, 1, 0, 2,  0, 0, 0, 1, 1, 0, 0, 1,
  1, 0, 1, 0, 0, 1, 1, 1,  1, 1, 0, 0, 1, 1, 0, 1,
  1, 0, 1, 1, 0, 0, 1, 1,  1, 1, 1, 1, 1, 0, 0, 1,
  1, 0, 0, 1, 1, 0, 1, 0,  1, 0, 0, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 0, 1, 1,  1, 1, 0, 1, 1, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 2, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 0, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 1,  1, 1, 0, 1, 1, 1, 0, 1,
  1, 0, 1, 1, 0, 1, 1, 1,  1, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 1, 0, 0, 0, 1,  1, 1, 0, 1, 0, 1, 1, 1,
  1, 0, 1, 1, 1, 1, 0, 1,  0, 1, 0, 1, 0, 0, 0, 1,
  1, 0, 0, 0, 1, 1, 0, 1,  1, 1, 1, 1, 0, 1, 0, 1,
  1, 2, 1, 0, 1, 0, 0, 0,  2, 0, 0, 0, 0, 1, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
};

byte labyrinthPool[2][2][16 * 16] = {
  {
    {
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 5, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 1, 0, 1, 1, 0, 2,  0, 0, 0, 1, 1, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 1, 1, 0, 0, 1, 1,  1, 1, 1, 1, 1, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 1, 0, 0, 0, 0, 1, 1,  1, 1, 0, 1, 1, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 2, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 0, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 1, 1, 0, 1, 1, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 1, 1, 1, 1, 0, 1,  0, 1, 0, 1, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 2, 1, 0, 1, 0, 0, 0,  2, 0, 0, 0, 0, 1, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 5, 1, 0, 0, 0, 0, 1,  1, 1, 0, 0, 0, 0, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 2,  0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 1, 0, 0, 1, 1, 1,  1, 1, 0, 0, 1, 1, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 1, 1, 0, 1, 0,  1, 0, 0, 0, 0, 0, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 2, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 0, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 1, 0, 1, 1, 1, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 1, 0, 0, 0, 1,  1, 1, 0, 1, 0, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 1, 1, 0, 1,  1, 1, 1, 1, 0, 1, 0, 1,
      1, 2, 1, 0, 1, 0, 0, 0,  2, 0, 0, 0, 0, 1, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    }
  },
  {
    {
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 5, 1, 0, 0, 0, 0, 1,  1, 1, 0, 0, 0, 0, 1, 1,
      1, 0, 1, 0, 1, 1, 0, 2,  0, 0, 0, 1, 1, 0, 0, 1,
      1, 0, 1, 0, 0, 1, 1, 1,  1, 1, 0, 0, 1, 1, 0, 1,
      1, 0, 1, 1, 0, 0, 1, 1,  1, 1, 1, 1, 1, 0, 0, 1,
      1, 0, 0, 1, 1, 0, 1, 0,  1, 0, 0, 0, 0, 0, 1, 1,
      1, 1, 0, 0, 0, 0, 1, 1,  1, 1, 0, 1, 1, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 2, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 0, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 1, 0, 1, 1, 1, 0, 1,
      1, 0, 1, 1, 0, 1, 1, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 1, 0, 0, 0, 1,  1, 1, 0, 1, 0, 1, 1, 1,
      1, 0, 1, 1, 1, 1, 0, 1,  0, 1, 0, 1, 0, 0, 0, 1,
      1, 0, 0, 0, 1, 1, 0, 1,  1, 1, 1, 1, 0, 1, 0, 1,
      1, 2, 1, 0, 1, 0, 0, 0,  2, 0, 0, 0, 0, 1, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 5, 1, 0, 0, 0, 0, 1,  1, 1, 0, 0, 0, 0, 1, 1,
      1, 0, 1, 0, 1, 1, 0, 2,  0, 0, 0, 1, 1, 0, 0, 1,
      1, 0, 1, 0, 0, 1, 1, 1,  1, 1, 0, 0, 1, 1, 0, 1,
      1, 0, 1, 1, 0, 0, 1, 1,  1, 1, 1, 1, 1, 0, 0, 1,
      1, 0, 0, 1, 1, 0, 1, 0,  1, 0, 0, 0, 0, 0, 1, 1,
      1, 1, 0, 0, 0, 0, 1, 1,  1, 1, 0, 1, 1, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 2, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 0, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 1, 0, 1, 1, 1, 0, 1,
      1, 0, 1, 1, 0, 1, 1, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 1, 0, 0, 0, 1,  1, 1, 0, 1, 0, 1, 1, 1,
      1, 0, 1, 1, 1, 1, 0, 1,  0, 1, 0, 1, 0, 0, 0, 1,
      1, 0, 0, 0, 1, 1, 0, 1,  1, 1, 1, 1, 0, 1, 0, 1,
      1, 2, 1, 0, 1, 0, 0, 0,  2, 0, 0, 0, 0, 1, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    }
  }
};


byte playerPositionX = 1;
byte playerPositionY = 1;
byte currentRound = 0;
byte life = 5;

int maxLabs = 2;
int up;
int down;
int left;
int right;

char player = 'z';
//char player = 'p';

bool block;
bool gameend = true;
bool newgame = true;
bool waiting = false;

void setup() {

  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  Serial.begin(9600);
  //Serial.println("drawLab:");
  matrix.begin();

  // draw a pixel in solid white

  matrix.drawPixel(0, 0, matrix.Color333(7, 7, 7));
  checkRound();

}

void loop() {

  up = digitalRead(UP);
  down = digitalRead(DOWN);
  left = digitalRead(LEFT);
  right = digitalRead(RIGHT);
  //enable game reset after win or lose
  newGameStarts();
  someoneWaits();


  //disable long press button
  if (up == LOW && down == LOW && left == LOW && right == LOW) {
    block = false;
  }

  if (player == 'p') {
    if (life == 0 && !gameend && !waiting) {
      drawGameover();
      gameend = true;
    }

    if (life > 0 && !gameend) {
      if (up == HIGH && !block) {
        movePlayer(1);
        block = true;
      }
      if (down == HIGH && !block) {
        movePlayer(2);
        block = true;
      }
      if (left == HIGH && !block) {
        movePlayer(3);
        block = true;
      }
      if (right == HIGH && !block) {
        movePlayer(4);
        block = true;
      }
    }

  } else if (player == 'w') {
    char movement = 'z';
    if (Serial.available()) {
      movement = reciveData();
    }
    if (life == 0 && !gameend && !waiting) {
      drawGameover();
      gameend = true;
    }

    if (life > 0 && !gameend) {
      if (movement == 'u') {
        movePlayer(1);
      }
      if (movement == 'd') {
        movePlayer(2);
      }
      if (movement == 'l') {
        movePlayer(3);
      }
      if (movement == 'r') {
        movePlayer(4);
      }
      if (movement == 'i') {
        displayLife();
        lifeLost(true);
      }
    }
  } else {
    if (Serial.available()) {
      player = reciveData();
    }
  }
}

void newGameStarts() {
  if (newgame) {
    if (left == HIGH && !block) {
      block = true;
      Serial.print('s');
      waiting = true;
      player = 'p';
      newgame = false;
      life = 0;
      for (int k = 0; k < sizeof(labyrinth); k++) {
        labyrinth[k] -= 5; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
      }
    }
    if (Serial.available()) {
      char data = reciveData();
      if (data == 's') {
        player = 'w';
        newgame = false;
        waiting = true;
        life = 0;
        for (int k = 0; k < sizeof(labyrinth); k++) {
          labyrinth[k] -= 5; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
        }
      }
    }
  }
}
void drawGameover() {
  for (int k = 0; k < sizeof(labyrinth); k++) {
    labyrinth[k] -= 5; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
  }
  drawLab((byte*) &labyrinth);
  matrix.setCursor(5, 9);   // start at top left, with one pixel of spacing
  matrix.setTextSize(1);    // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print('G');
  matrix.print('A');
  matrix.print('M');
  matrix.print('E');
  matrix.setCursor(5, 18);
  matrix.print('O');
  matrix.print('V');
  matrix.print('E');
  matrix.print('R');
  newgame = true;
}

void someoneWaits() {
  if (waiting) {
    drawSomeoneWaits();
    if (up == HIGH && !block && player != 'p') {
      block = true;
      Serial.print('w');
      gameend = false;
      playerPositionX = 1;
      playerPositionY = 1;
      currentRound = 0;
      life = 5;
      waiting = false;
      int labNr = random(0, maxLabs - 1);
      Serial.print(labNr);
      for (int k = 0; k < sizeof(labyrinth); k++) {
        labyrinth[k] = labyrinthPool[labNr][0][k];
      }
      block = false;
      checkRound();
    }


    if (Serial.available()) {
      char startcode = reciveData();
      if (startcode == 'a') {
        gameend = false;
        playerPositionX = 1;
        playerPositionY = 1;
        currentRound = 0;
        life = 5;
        waiting = false;
        while (Serial.available() == 0) {
        }
        if (Serial.available()) {
          int incomingByte = reciveData();
          int labNr = (incomingByte - '0');
          for (int k = 0; k < sizeof(labyrinth); k++) {
            labyrinth[k] = labyrinthPool[labNr][1][k];
          }
        }
        checkRound();
      }
    }
  }
}

void drawSomeoneWaits() {
  delay(700);
  drawLab((byte*) &labyrinth);
  delay(700);
  matrix.setCursor(5, 8);   // start at top left, with one pixel of spacing
  matrix.setTextSize(0.1);    // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print('W');
  matrix.print('A');
  matrix.print('I');
  matrix.print('T');
  matrix.setCursor(7, 18);
  matrix.print('I');
  matrix.print('N');
  matrix.print('G');
}


void draw(byte x, byte y, byte tmp ) {
  x *= 2;
  y *= 2;
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  if (tmp == 1) {
    r = 68;
    g = 18;
    b = 166;
  } else if (tmp == 2) {
    r = 214;
    g = 204;
    b = 32;
  } else if (tmp == 3) {
    r = 172;
    g = 163;
    b = 14;
  } else if (tmp == 4) {
    g = 250;
  } else if (tmp == 5) {
    r = 140;
    g = 140;
    b = 14;
  }

  matrix.drawPixel(x, y, matrix.Color888(r, g, b));
  matrix.drawPixel(x, y + 1, matrix.Color888(r, g, b));
  matrix.drawPixel(x + 1, y, matrix.Color888(r, g, b));
  matrix.drawPixel(x + 1, y + 1, matrix.Color888(r, g, b));
}

void drawLab(byte *lab) {

  for (int e = 0; e < 16 * 16; e++) {
    byte tmp = *(lab + e);
    int j = e % 16;
    int i = e / 16;
    draw(j, i, tmp);
  }
  displayLife();
}

void displayLife() {
  if (life > 0) {
    for (int i = 0; i < life + 1; i++) {
      matrix.drawPixel(i, 0, matrix.Color888(68, 18, 166));
    }
  }

  for (int i = 0; i < life; i++) {
    matrix.drawPixel(i, 0, matrix.Color888(255, 0, 0));
  }

  if (gameend) {
    for (int i = 0; i < life + 1; i++) {
      matrix.drawPixel(i, 0, matrix.Color888(0, 0, 0));
    }
  }
}


void checkRound() {
  bool win = 0;
  switch (currentRound) {
    case 0:
      for (int i = 8; i < 16; i++) {
        labyrinth[i] -= 3; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
        labyrinth[i + 16] -= 3;
        labyrinth[i + 32] -= 3;
        labyrinth[i + 48] -= 3;
        labyrinth[i + 64] -= 3;
        labyrinth[i + 80] -= 3;
        labyrinth[i + 96] -= 3;
      }
      for (int i = 120; i < sizeof(labyrinth); i++) {
        labyrinth[i] -= 3;
      }
      break;
    case 1:
      for (int i = 8; i < 16; i++) {
        labyrinth[i] += 3; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
        labyrinth[i + 16] += 3;
        labyrinth[i + 32] += 3;
        labyrinth[i + 48] += 3;
        labyrinth[i + 64] += 3;
        labyrinth[i + 80] += 3;
        labyrinth[i + 96] += 3;
        labyrinth[i + 112] += 3;
      }
      *(labyrinth + (playerPositionY * 16) + playerPositionX) = 0;
      break;
    case 2:
      for (int k = 136; k < 144; k++) {
        labyrinth[k] += 3; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
        labyrinth[k + 16] += 3;
        labyrinth[k + 32] += 3;
        labyrinth[k + 48] += 3;
        labyrinth[k + 64] += 3;
        labyrinth[k + 80] += 3;
        labyrinth[k + 96] += 3;
        labyrinth[k + 112] += 3;
      }

      *(labyrinth + (playerPositionY * 16) + playerPositionX) = 0;
      break;
    case 3:
      for (int k = 128; k < 136; k++) {
        labyrinth[k] += 3; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
        labyrinth[k + 16] += 3;
        labyrinth[k + 32] += 3;
        labyrinth[k + 48] += 3;
        labyrinth[k + 64] += 3;
        labyrinth[k + 80] += 3;
        labyrinth[k + 96] += 3;
        labyrinth[k + 112] += 3;
      }
      *(labyrinth + (playerPositionY * 16) + playerPositionX) = 0;
      break;
    case 4:
      win = true;
      break;
  }

  if (!win) {
    drawLab((byte*) &labyrinth);
    draw(playerPositionX, playerPositionY, 4);
  } else {
    for (int k = 0; k < sizeof(labyrinth); k++) {
      labyrinth[k] -= 5; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
    }
    drawLab((byte*) &labyrinth);
    gameend = true;
    matrix.setCursor(7, 0);   // start at top left, with one pixel of spacing
    matrix.setTextSize(1);    // size 1 == 8 pixels high
    matrix.setTextColor(matrix.Color333(0, 7, 0));
    matrix.print('W');
    matrix.print('I');
    matrix.print('N');
    newgame = true;
  }

}


void movePlayer(byte direction) {
  draw(playerPositionX, playerPositionY, *(labyrinth + (playerPositionX + 16 * playerPositionY)));
  //byte temp = labyrinth[playerPositionY-1][playerPositionX];

  byte above = *(labyrinth + (playerPositionY * 16) + playerPositionX - 16);
  byte below = *(labyrinth + (playerPositionY * 16) + playerPositionX + 16);
  byte left = *(labyrinth + (playerPositionY * 16) + playerPositionX - 1);
  byte right = *(labyrinth + (playerPositionY * 16) + playerPositionX + 1);
  /*Serial.print("above: ");
    Serial.println(above);
    Serial.print("below: ");
    Serial.println(below);
    Serial.print("left: ");
    Serial.println(left);
    Serial.print("right: ");
    Serial.println(right);*/
  char movement = 'k';
  delay(500);
  if (Serial.available()) {
  movement = reciveData();
  }
  switch (direction) {
    case 1:
      if ( above == 1 || movement == 'i') {
        if (movement == 'i') {
          lifeLost(true);
        } else {
          lifeLost(false);
        }
      } else if (above != 1) {
        playerPositionY -= 1;
        Serial.print('u');
      }
      break;
    case 2:
      if (  below == 1 || movement == 'i') {
        if (movement == 'i') {
          lifeLost(true);
        } else {
          lifeLost(false);
        }
      } else if (below != 1) {
        playerPositionY += 1;
        Serial.print('d');
      }
      break;
    case 3:
      if (left == 1 || movement == 'i') {
        if (movement == 'i') {
          lifeLost(true);
        } else {
          lifeLost(false);
        }

      } else if (left != 1) {
        playerPositionX -= 1;
        Serial.print('l');
      } else {
        lifeLost(false);
      }
      break;
    case 4:
      if (right == 1 || movement == 'i') {
        if (movement == 'i') {
          lifeLost(true);
        } else {
          lifeLost(false);
        }
      } else if (right != 1) {
        playerPositionX += 1;
        Serial.print('r');
      }
      break;
  }

  draw(playerPositionX, playerPositionY, 4);
  if (*(labyrinth + (playerPositionY * 16) + playerPositionX) == 2) {
    currentRound += 1;
    checkRound();
  }

}
void lifeLost(bool external) {
  life -= 1;
  displayLife();
  if (!external) {
    Serial.print('i');
  }
}

char reciveData() {
  char incomingByte = Serial.read();
  return char(incomingByte);

}

