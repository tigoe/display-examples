/*
Super Duper Knight Rider
 for Arduino Mega
 
 This example controls two 8x8 LED matrices, lighting one LED at a time, 
 then bouncing back to the beginning.
 
 created 29 Mar 2009
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
int row[] = {
  22,23,27,49,28,45,43,25};

int col[] = {
  47,41,51,39,26,53,24,29};


int row2[] = {
  9,8,4,35,3,10,11,6};

int col2[] = {
  34,12,36,13,5,37,7,2};



void setup() {
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins for matrix 1:
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT);  
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off: 
    digitalWrite(col[thisPin], HIGH);   

    // initialize the output pins for matrix 2:
    pinMode(col2[thisPin], OUTPUT); 
    pinMode(row2[thisPin], OUTPUT); 

    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off:   
    digitalWrite(col2[thisPin], HIGH);   
  }
}

void loop() {
  // light up the first matrix:
  // iterate over the rows (anodes):
  for (int thisrow = 0; thisrow < 8; thisrow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisrow], HIGH);
    // iterate over the cols (cathodes):
    for (int thiscol = 0; thiscol < 8; thiscol++) {
      // when the row is high and the col is low,
      // the LED where they meet turns on:
      digitalWrite(col[thiscol], LOW);
      delay(50);
      // take the col pin (cathode) high to turn the LED off:
      digitalWrite(col[thiscol], HIGH);       
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisrow], LOW);
  }

  // light up the second matrix:

  // iterate over the rows (anodes):
  for (int thisrow = 0; thisrow < 8; thisrow++) {
    // take the row pin (anode) high:
    digitalWrite(row2[thisrow], HIGH);
    // iterate over the cols (cathodes):    
    for (int thiscol = 0; thiscol < 8; thiscol++) {
      // when the row is high and the col is low,
      // the LED where they meet turns on:
      digitalWrite(col2[thiscol], LOW);
      delay(50);
      // take the col pin (cathode) high to turn the LED off:
      digitalWrite(col2[thiscol], HIGH);       
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row2[thisrow], LOW);
  }

  // do the same to go backwards, counting backwards:

  // second matrix in reverse:
  for (int thisrow = 7; thisrow > 0; thisrow--) {
    digitalWrite(row2[thisrow], HIGH);
    for (int thiscol = 7; thiscol >0; thiscol--) {
      digitalWrite(col2[thiscol], LOW);
      delay(50);
      digitalWrite(col2[thiscol], HIGH);       
    }
    digitalWrite(row2[thisrow], LOW);
  }
  // first matrix in reverse:
  for (int thisrow = 7; thisrow > 0; thisrow--) {
    digitalWrite(row[thisrow], HIGH);
    for (int thiscol = 7; thiscol >0; thiscol--) {
      digitalWrite(col[thiscol], LOW);
      delay(50);
      digitalWrite(col[thiscol], HIGH);       
    }
    digitalWrite(row[thisrow], LOW);
  }
}
