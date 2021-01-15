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
int row[] = {2, 7, A7, 5, A0, A6, A1, A4};
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
}

void loop() {
  // take each row high:
  for (int r = 0; r < 8; r++) {
    digitalWrite(row[r], HIGH);
    // Take each column low to turn on (row, column):
    for (int c = 0; c < 8; c++) {
      int p = c + (r * 8);
      digitalWrite(col[c], !pixels[p]);
    }
    // take the row low to turn off the whole row:
    digitalWrite(row[r], LOW);
  }
}
