#include "FastLED.h"
#include <Keypad.h>

// Mode definitions
#define SETUP 1
#define SHUTTLE 2
#define SIMPLE_SLOW 3
#define SIMPLE_QUICK 4
#define RANDOM_10P 5
#define RANDOM_20P 6
#define RANDOM_30P 7
#define RANDOM_40P 8
#define RANDOM_50P 9
#define RANDOM_60P 10
#define RANDOM_70P 11
#define RANDOM_80P 12
#define RANDOM_90P 13
#define RANDOM_100P 14
#define TRAINING_LOOP_3A_3R 15
#define TRAINING_LOOP_L_R 16
int mode = SETUP;

// Movement definitions
#define HOLDING 0
#define ADVANCE 1
#define RETREAT 2
#define LUNGE_ENEMY 3
#define LUNGE 4
#define ADVANCE_LUNGE 5
#define FLECHE 6
byte movement = HOLDING;
int movementStart = 0;

// Set definitions for LED strip
#define NUM_LEDS 115
#define NUM_LEDS_PER_METER 30
#define REVERSE_MODE 1
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

// Set definitions for keypad
#define LEDPIN 13
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {11, 10, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/* Clear the full length of the led strip */
void clear () {
  fill_solid( &(leds[0]), NUM_LEDS, CRGB::Black );
  FastLED.show();
}

/* Show position */
void position ( int x, int r ) {
  // Fix over- and underflow
  if ( x - r < -1 ) {
    x = 0;
  } else if ( x + r >= NUM_LEDS ) {
    x = NUM_LEDS - r - 1;
  }

  if ( r <= 1 ) {
    r = 1;
  }

#ifdef REVERSE_MODE
  x = map(x, 0, NUM_LEDS, NUM_LEDS, 0);
#endif 

  
  leds[x] = CRGB::Blue;
  for ( int i = 1; i <= r; i++ ) {
    leds[x-i] = CRGB( 255*(r-i)/r, 0, 0);
    leds[x+i] = CRGB( 255*(r-i)/r, 0, 0);
  }
  FastLED.show();
}

/* Simulate movement */
void move (int moveType, int speed, int startLed) {
  // Initialize ending led variable
  int endLed = startLed;
  if ( startLed > (NUM_LEDS - 50) ) { moveType = RETREAT; }
  if ( startLed < 50 ) { moveType = ADVANCE; }
  
  // Set all leds to black
  clear();

  // Initialize speed recalculation (percentages to delays)
  if(speed < 10) { speed = 10; }
  int delayTime = map(speed, 10, 100, 1000, 25);
  
  // Start moving
  switch(moveType) {
    case HOLDING:
      position(startLed, 2);
      FastLED.delay(delayTime);
      movementStart = startLed;
      break;
    case ADVANCE:
      position(startLed, 2);
      FastLED.delay(delayTime);
      for(byte i = 1; i < 10; i++) {
        clear();
        position(startLed + i, 2);
        FastLED.delay(5);
      }
      FastLED.delay(delayTime);
      endLed = startLed + 10;
      movementStart = endLed;
      break;
    case RETREAT:
      position(startLed, 2);
      FastLED.delay(delayTime);
      for(byte i = 1; i < 10; i++) {
        clear();
        position(startLed - i, 2);
        FastLED.delay(5);
      }
      FastLED.delay(delayTime);
      endLed = startLed - 10;
      movementStart = endLed;
      break;
    case LUNGE:
      position(startLed, 2);
      FastLED.delay(delayTime);
      for(byte i = 1; i < 40; i++) {
        clear();
        position(startLed + i, 2);
        FastLED.delay(5);
      }
      FastLED.delay(delayTime);
      endLed = startLed + 40;
      movementStart = endLed;
      break;
    case LUNGE_ENEMY:
      position(startLed, 2);
      FastLED.delay(delayTime);
      for(byte i = 1; i < 40; i++) {
        clear();
        position(startLed + i, 2);
        FastLED.delay(5);
      }
      FastLED.delay(delayTime);
      endLed = startLed + 40;
      movementStart = endLed;
      break;
    case ADVANCE_LUNGE:
      movementStart = endLed;
      movementStart = endLed;
      break;
    case FLECHE:
      endLed = startLed;
      movementStart = endLed;
      break;
    default:
      endLed = startLed;
      movementStart = endLed;
      break;
  }

  if ( movementStart < 0 ) { movementStart =  0; }
  if ( movementStart > NUM_LEDS ) { movementStart =  NUM_LEDS; }
}

void keypadEvent(KeypadEvent key){
  digitalWrite(LEDPIN,!digitalRead(LEDPIN)); 
  
  switch (key) {
    case 'A':
      mode = SETUP;
      break;
    case 'B':
      mode = SHUTTLE;
      break;
    case 'C':
      mode = SIMPLE_SLOW;
      break;
    case 'D':
      mode = SIMPLE_QUICK;
      break;
    case '1':
      mode = RANDOM_10P;
      break;
    case '2':
      mode = RANDOM_20P;
      break;
    case '3':
      mode = RANDOM_30P;
      break;
    case '4':
      mode = RANDOM_40P;
      break;
    case '5':
      mode = RANDOM_50P;
      break;
    case '6':
      mode = RANDOM_60P;
      break;
    case '7':
      mode = RANDOM_70P;
      break;
    case '8':
      mode = RANDOM_80P;
      break;
    case '9':
      mode = RANDOM_90P;
      break;
    case '0':
      mode = RANDOM_100P;
      break;
    case '*':
      mode = TRAINING_LOOP_3A_3R;
      break;
    case '#':
      mode = TRAINING_LOOP_L_R;
      break;
    default:
      break;
  }
}

void setup() {
  pinMode(LEDPIN, OUTPUT);              // Sets the digital pin as output.
  digitalWrite(LEDPIN, HIGH);           // Turn the LED on.
  
  delay(2000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);

  keypad.addEventListener(keypadEvent);
}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
  switch(mode) {
    case SETUP:
      fill_solid( &(leds[0]), NUM_LEDS, CRGB::Red );
      FastLED.delay(500);
      fill_solid( &(leds[0]), NUM_LEDS, CRGB::Green );
      FastLED.delay(500);
      fill_solid( &(leds[0]), NUM_LEDS, CRGB::Blue );
      FastLED.delay(500);
      fill_solid( &(leds[0]), NUM_LEDS, CRGB::White );
      FastLED.delay(500);
      clear();
      break;
    case SHUTTLE:
      position(0, 2);         // end
      position(NUM_LEDS/2, 2); // middle
      position(NUM_LEDS, 2);   // start
      break;
    case SIMPLE_SLOW:
      for ( int i = 0; i < NUM_LEDS; i++ ) {
        position(NUM_LEDS - i, 2);
        FastLED.delay(25);
        clear();
      }
      break;
    case SIMPLE_QUICK:
      for ( int i = 0; i < NUM_LEDS; i++ ) {
        position(NUM_LEDS - i, 2);
        FastLED.delay(5);
        clear();
      }
      break;
    case RANDOM_10P:
      movement = random(0,4);
      move(movement, 10, movementStart);
      break;
    case RANDOM_20P:
      movement = random(0,4);
      move(movement, 20, movementStart);
      break;
    case RANDOM_30P:
      movement = random(0,4);
      move(movement, 30, movementStart);
      break;
    case RANDOM_40P:
      movement = random(0,4);
      move(movement, 40, movementStart);
      break;
    case RANDOM_50P:
      movement = random(0,4);
      move(movement, 50, movementStart);
      break;
    case RANDOM_60P:
      movement = random(0,4);
      move(movement, 60, movementStart);
      break;
    case RANDOM_70P:
      movement = random(0,4);
      move(movement, 70, movementStart);
      break;
    case RANDOM_80P:
      movement = random(0,4);
      move(movement, 80, movementStart);
      break;
    case RANDOM_90P:
      movement = random(0,4);
      move(movement, 90, movementStart);
      break;
    case RANDOM_100P:
      movement = random(0,4);
      move(movement, 100, movementStart);
      break;
    case TRAINING_LOOP_3A_3R:
      move(ADVANCE, 50, NUM_LEDS/3);
      move(ADVANCE, 50, NUM_LEDS/3);
      move(ADVANCE, 50, NUM_LEDS/3);
      move(RETREAT, 50, NUM_LEDS/3);
      move(RETREAT, 50, NUM_LEDS/3);
      move(RETREAT, 50, NUM_LEDS/3);
      break;
    case TRAINING_LOOP_L_R:
      move(LUNGE, 50, NUM_LEDS/3);
      move(RETREAT, 50, NUM_LEDS/3);
      break;
    default:
      break;
  }
}
