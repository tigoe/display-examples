
int col[] = {6, A2, A3, 3, A5, 4, 8, 9};
int row[] = {2, 7, A7, 5, A0, A6, A1, A4};

void setup() {
  // initialize all the pins as outputs:
  for (int i = 0; i < 8; i++) {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
    // set the column pins HIGH
    digitalWrite(col[i], HIGH);
  }
}

void loop() {
  // take the rows high:
  for (int r = 0; r < 8; r++) {
    digitalWrite(row[r], HIGH);
    // Take each column low to turn on (row, column):
    for (int c = 0; c < 8; c++) {
      digitalWrite(col[c], LOW);
      delay(100);
      // take the col high to turn off the LED:
      digitalWrite(col[c], HIGH);
    }
    // take the row low to turn off the whole row:
    digitalWrite(row[r], LOW);
  }
}
