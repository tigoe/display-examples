/*
  8x8 LED control
  For https://www.digikey.com/en/products/detail/seeed-technology-co-ltd/104020149/10451891
  or
  https://www.digikey.com/en/products/detail/seeed-technology-co-ltd/104020150/10451906

  Turns on one LED at a time, at (row, column)

  created 31 Oct 2020
  by Tom Igoe
*/
int col[] = {6, A2, A3, 3, A5, 4, 8, 9};
int row[] = {2, 7, A7, 5, 12, A6, 13, A4};
int pixels[] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  1, 0, 0, 0, 0, 0, 0, 1,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

void setup() {
  // initialize all the pins as outputs:
  for (int i = 0; i < 8; i++) {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
    // set the column pins HIGH to ensure that their LEDs are off:
    digitalWrite(col[i], HIGH);
  }
  Serial.begin(9600);
}

void loop() {
  int x = 0; //analogRead(A0) / 128;
  delay(1);
  int y = 2; // analogRead(A1) / 128;
  // take each row high:
  for (int r = 0; r < 8; r++) {
    digitalWrite(row[r], HIGH);
    // Take each column low to turn on (row, column):
    for (int c = 0; c < 8; c++) {
      digitalWrite(col[c], HIGH);
      if (x == c && y == r) {
        digitalWrite(col[c], LOW);
      } else {
        digitalWrite(col[c], HIGH);
      }
    }
    // take the row low to turn off the whole row:
    digitalWrite(row[r], LOW);
  }
}
