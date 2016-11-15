#include "FastLED.h"
#include <Keypad.h>

// Mode definitions
#define SETUP 1
#define SHUTTLE 2
#define SIMPLE_SLOW 3
#define SIMPLE_QUICK 4
#define RANDOM 5
#define TRAINING_LOOP_3A_3R 6
#define TRAINING_LOOP_L_R 7

// Movement definitions
#define HOLDING 0
#define ADVANCE 1
#define RETREAT 2
#define LUNGE_ENEMY 3
#define LUNGE 4
#define ADVANCE_LUNGE 5
#define FLECHE 6

// Set definitions for LED strip
#define NUM_LEDS 115
#define NUM_LEDS_PER_METER 30
#define REVERSE_MODE 1
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

// Defining global variables
int g_mode = SETUP;
byte g_movementSpeed = 10;
byte g_movement = HOLDING;
int g_movementStart = 0;

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
      g_movementStart = startLed;
      break;
    case ADVANCE:
      position(startLed, 2);
      FastLED.delay(delayTime);
      for(byte i = 1; i < 20; i++) {
        clear();
        position(startLed + i, 2);
        FastLED.delay(5);
      }
      FastLED.delay(delayTime);
      endLed = startLed + 19;
      break;
    case RETREAT:
      position(startLed, 2);
      FastLED.delay(delayTime);
      for(byte i = 1; i < 20; i++) {
        clear();
        position(startLed - i, 2);
        FastLED.delay(5);
      }
      FastLED.delay(delayTime);
      endLed = startLed - 19;
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
      endLed = startLed + 39;
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
      endLed = startLed + 39;
      break;
    case ADVANCE_LUNGE:
      endLed = startLed;
      break;
    case FLECHE:
      endLed = startLed;
      break;
    default:
      endLed = startLed;
      break;
  }

  if ( g_movementStart < 0 ) { setMovementStart(0); }
  if ( g_movementStart > NUM_LEDS ) { setMovementStart(NUM_LEDS); }
  else { setMovementStart(endLed); }
}

byte getRandomMovement() {
  int randNumber = random(0,100);
  if ( randNumber < 30 ) { return HOLDING; }
  else if ( randNumber >= 30 && randNumber < 60 ) { return ADVANCE; }
  else if ( randNumber >= 60 && randNumber < 90 ) { return  RETREAT; }
  else { return LUNGE; }
}

byte getMode() {
  return g_mode;
}

byte getMovementSpeed() {
  return g_movementSpeed;
}

void setMovementSpeed(int movementSpeed) {
  g_movementSpeed = movementSpeed;
}

int getMovementStart() {
  return g_movementStart;
}

void setMovementStart(int movementStart) {
  g_movementStart = movementStart;
}

void setMode(){   
  switch (keypad.getKey()) {
    case 'A':
      g_mode = SETUP;
      break;
    case 'B':
      g_mode = SHUTTLE;
      break;
    case 'C':
      g_mode = SIMPLE_SLOW;
      break;
    case 'D':
      g_mode = SIMPLE_QUICK;
      break;
    case '1':
      g_mode = RANDOM;
      setMovementSpeed(10);
      break;
    case '2':
      g_mode = RANDOM;
      setMovementSpeed(20);
      break;
    case '3':
      g_mode = RANDOM;
      setMovementSpeed(30);
      break;
    case '4':
      g_mode = RANDOM;
      setMovementSpeed(40);
      break;
    case '5':
      g_mode = RANDOM;
      setMovementSpeed(50);
      break;
    case '6':
      g_mode = RANDOM;
      setMovementSpeed(60);
      break;
    case '7':
      g_mode = RANDOM;
      setMovementSpeed(70);
      break;
    case '8':
      g_mode = RANDOM;
      setMovementSpeed(80);
      break;
    case '9':
      g_mode = RANDOM;
      setMovementSpeed(90);
      break;
    case '0':
      g_mode = RANDOM;
      setMovementSpeed(100);
      break;
    case '*':
      g_mode = TRAINING_LOOP_3A_3R;
      break;
    case '#':
      g_mode = TRAINING_LOOP_L_R;
      break;
    default:
      break;
  }
}

void setup() {  
  delay(2000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
  setMode();
  switch(getMode()) {
    case SETUP:
      fill_solid( &(leds[0]), NUM_LEDS, CRGB::Red );
      setMode();
      FastLED.delay(500);
      fill_solid( &(leds[0]), NUM_LEDS, CRGB::Green );
      setMode();
      FastLED.delay(500);
      fill_solid( &(leds[0]), NUM_LEDS, CRGB::Blue );
      setMode();
      FastLED.delay(500);
      fill_solid( &(leds[0]), NUM_LEDS, CRGB::White );
      setMode();
      FastLED.delay(500);
      clear();
      break;
    case SHUTTLE:
      position(0, 2);           // end
      position(NUM_LEDS/2, 2);  // middle
      position(NUM_LEDS, 2);    // start
      break;
    case SIMPLE_SLOW:
      for ( int i = 0; i < NUM_LEDS; i++ ) {
        setMode();
        position(NUM_LEDS - i, 2);
        FastLED.delay(25);
        clear();
      }
      break;
    case SIMPLE_QUICK:
      for ( int i = 0; i < NUM_LEDS; i++ ) {
        setMode();
        position(NUM_LEDS - i, 2);
        FastLED.delay(5);
        clear();
      }
      break;
    case RANDOM:
      move(getRandomMovement(), getMovementSpeed(), getMovementStart());
      break;
    case TRAINING_LOOP_3A_3R:
      setMovementStart(NUM_LEDS/3);
      move(ADVANCE, 50, getMovementStart());
      setMode();
      move(ADVANCE, 50, getMovementStart());
      setMode();
      move(ADVANCE, 50, getMovementStart());
      setMode();
      move(RETREAT, 50, getMovementStart());
      setMode();
      move(RETREAT, 50, getMovementStart());
      setMode();
      move(RETREAT, 50, getMovementStart());
      setMode();
      break;
    case TRAINING_LOOP_L_R:
      setMovementStart(NUM_LEDS/3);
      move(LUNGE, 50, getMovementStart());
      setMode();
      move(RETREAT, 50, getMovementStart());
      setMode();
      break;
    default:
      break;
  }
}
