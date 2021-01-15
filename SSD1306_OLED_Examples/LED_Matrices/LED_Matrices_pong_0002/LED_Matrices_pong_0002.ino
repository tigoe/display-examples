/*
  8x8 LED matrix pong
  for Arduino Mega

  This example controls two 8x8 LED matrices in a game of pong.
  It takes input from two analog inputs to set the
  paddles, and moves the ball accordingly.

  created 1 Apr 2009
  updated 31 Oct 2020
  by Tom Igoe

  The matrices used are labeled  HS-788AS.  They were bought surplus.
  They are laid out as follows
  (warning: yours might have different pin configurations):

  rows are the anodes
  cols are the cathodes

  label HS-788AS is on the left side of the chip
  _________
  col 4  ----|         |---- row 1
  col 2  ----|         |---- row 2
  row 7  ----|         |---- col 7
  row 6  ----|         |---- row 8
  col 1  ----|         |---- col 5
  row 4  ----|         |---- row 3
  col 3  ----|         |---- row 5
  col 6  ----|         |---- col 8
  ---------

  Pin numbers:
  Matrix 1:
  2,3,4,5,6,7,8,9,12,11,12,13, 34, 35, 36, 37

  Matrix 2:
  22,23,24,25,26,27,28,29,30,31,38,39,41,43,45,47,49,51,53

*/

// define the edges of the screen:
const int  LEFT = 0;
const int  RIGHT = 15;
const int  TOP = 0;
const int  BOTTOM = 7;

int pixels[16][8];           // 2-dimensional array of pixels

// 2-dimensional array of row pin numbers (for two matrices):
int row[2][8] = {
  {
    6, 11, 10, 3, 35, 4, 8, 9
  }
  ,
  {
    25, 43, 45, 28, 49, 27, 23, 22
  }
};

// 2-dimensional array of column pin numbers (for two matrices):
int col[2][8] = {
  {
    2, 7, 37, 5, 13, 36, 12, 34
  }
  ,
  {
    29, 24, 53, 26, 39, 51, 41, 47
  }
};

int ballX = 8;               // X position of the ball
int ballY = 4;               // Y position of the ball
int ballDirectionY = 1;      // X direction of the ball
int ballDirectionX = 1;      // Y direction of the ball

int rightPaddleY = 0;        // X position of the center of the right paddle
int leftPaddleY = 0;         // Y position of the center of the right paddle

long timeStamp = 0;          // time stamp to control the pauses between ball moves
long interval = 120;         // interval between ball moves, in milliseconds
boolean gamePaused = false;  // state of the game

void setup() {
  // initialize the I/O pins as outputs:

  // iterate over the two matrices:
  for (int thisMatrix = 0; thisMatrix < 2; thisMatrix++) {
    // iterate over the pins:
    for (int thisPin = 0; thisPin < 8; thisPin++) {
      // initialize the output pins:
      pinMode(col[thisMatrix][thisPin], OUTPUT);
      pinMode(row[thisMatrix][thisPin], OUTPUT);
      // take the col pins (i.e. the cathodes) high to ensure that
      // the LEDS are off:
      digitalWrite(col[thisMatrix][thisPin], HIGH);
    }
  }

  // initialize the pixel matrix:
  for (int x = 0; x < 16; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
    }
  }
}

void loop() {
  // read input:
  readSensors();
  // move the ball:
  if (gamePaused) {
    if (millis() - timeStamp > interval * 10) {
      // if enough time has passed, start the game again:
      gamePaused = false;
    }
  }
  // if the game isn't paused, and enough time between ball moves
  // has passed, move the ball and update the timestamp:
  else {
    if (millis() - timeStamp > interval) {
      moveBall();
      timeStamp = millis();
    }
  }
  // draw the screen:
  refreshScreen();
}

void readSensors() {
  // set the  left paddle to off:
  setPaddle(LEFT, leftPaddleY, HIGH);
  // set the right paddle to off:
  setPaddle(RIGHT, rightPaddleY, HIGH);

  // read the sensors for X and Y values:
  leftPaddleY = map(analogRead(0), 0, 1023, 0, 7);
  rightPaddleY = map(analogRead(1), 0, 1023, 0, 7);

  // set the  left paddle to on:
  setPaddle(LEFT, leftPaddleY, LOW);
  // set the right paddle to on:
  setPaddle(RIGHT, rightPaddleY, LOW);
}

void setPaddle(int paddleX, int paddleY, int state) {
  // set the last right paddle to on:
  pixels[paddleX][paddleY] = state;
  // set the bottom pixel of the paddle:
  if (paddleY < BOTTOM) {
    pixels[paddleX][paddleY + 1] = state;
  }

  // set the top pixel of the paddle:
  if (paddleY > TOP) {
    pixels[paddleX][paddleY - 1] = state;
  }
}

void moveBall() {
  // check to see if the ball is in the horizontal range
  // of the paddles:

  // right:
  if (ballX >= RIGHT - 1) {
    // if the ball's next Y position is between
    // the top and bottom of the paddle, reverse its  X direction:
    if ((ballY + ballDirectionY >= rightPaddleY - 1)
        && (ballY + ballDirectionY <= rightPaddleY + 1)) {
      // reverse the ball horizontal direction:
      ballDirectionX = -ballDirectionX;
    }
  }

  // left:
  if (ballX <= LEFT + 1) {
    // if the ball's next Y position is between
    // the top and bottom of the paddle, reverse its  X direction:
    if ((ballY + ballDirectionY >= leftPaddleY - 1 )
        && (ballY + ballDirectionY <= leftPaddleY + 1 )) {
      // reverse the ball horizontal direction:
      ballDirectionX = -ballDirectionX;
    }
  }

  // if the ball goes off the screen bottom,
  // reverse its Y direction:
  if (ballY == BOTTOM) {
    ballDirectionY = -ballDirectionY;
  }
  // if the ball goes off the screen top,
  // reverse its X direction:
  if (ballY == TOP) {
    ballDirectionY = -ballDirectionY;
  }

  // clear the ball's previous position:
  pixels[ballX][ballY] = HIGH;

  // if the ball goes off the screen left or right:
  if ((ballX == LEFT) || (ballX == RIGHT)) {
    // reset the ball:
    ballX = 8;
    ballY = 4;
    // pause  and note the time you paused:
    gamePaused = true;
    timeStamp = millis();
  }
  // increment the ball's position in both directions:
  ballX = ballX + ballDirectionX;
  ballY = ballY + ballDirectionY;

  // if the game isn't paused, set the ball
  // in its new position:
  if (!gamePaused) {
    // set the new position:
    pixels[ballX][ballY] = LOW;
  }
}

void refreshScreen() {
  // iterate over the matrices:
  for (int thisMatrix = 0; thisMatrix < 2; thisMatrix++) {
    // iterate over the rows (anodes):
    for (int thisRow = 0; thisRow < 8; thisRow++) {
      // take the row pin (anode) high:
      digitalWrite(row[thisMatrix][thisRow], HIGH);
      // iterate over the cols (cathodes):
      for (int thisCol = 0; thisCol < 8; thisCol++) {
        // get the state of the current pixel;
        int thisPixel = pixels[thisRow + (thisMatrix * 8)][thisCol];
        // when the row is HIGH and the col is LOW,
        // the LED where they meet turns on:
        digitalWrite(col[thisMatrix][thisCol], thisPixel);
        // turn the pixel off:
        digitalWrite(col[thisMatrix][thisCol], HIGH);
      }
      // take the row pin low to turn off the whole row:
      digitalWrite(row[thisMatrix][thisRow], LOW);
    }
  }
}
