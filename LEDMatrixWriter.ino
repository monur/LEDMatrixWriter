#define LED_WIDTH 8
#define LED_HEIGHT 8
#define BUFFER_LENGTH LED_WIDTH * LED_HEIGHT

// 2-dimensional array of row pin numbers:
const int row[8] = {2,7,19,5,13,18,12,16};

// 2-dimensional array of column pin numbers:
const int col[8] = {6,11,10,3,17,4,8,9};
byte pixels[8][8] = {
  {1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,1},
  {1,0,1,1,1,1,0,1},
  {1,1,0,0,0,0,1,1},
  {1,1,1,0,0,1,1,1},
  {1,1,0,1,1,0,1,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1}
};           

byte screenBuffer[BUFFER_LENGTH] = {0};

void setup(){
  // initialize the I/O pins as outputs
  // iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT);  
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off: 
    digitalWrite(col[thisPin], HIGH);    
  }
  Serial.begin(9600);
  delay(1000);
}
 
void loop(){
  while(Serial.available() > 0){
     Serial.readBytes(screenBuffer, BUFFER_LENGTH);
     Serial.write(screenBuffer, BUFFER_LENGTH);
     for(int i = 0; i < LED_WIDTH; i++){
       for(int j = 0; j < LED_HEIGHT; j++){
         pixels[i][j] = screenBuffer[i*LED_WIDTH + j] - '0';
       }
     }
  }
  draw();
}

void draw() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off:
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }
}

