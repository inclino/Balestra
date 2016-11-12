#include "FastLED.h"
#include <Keypad.h>

// Mode definitions
#define SETUP 0
#define SHUTTLE 1
#define SIMPLE_SLOW 2
#define SIMPLE_QUICK 3
#define RANDOM_SLOW 4
#define RANDOM_QUICK 5
int mode = SETUP;

// Movement definitions
#define ADVANCE 0
#define RETREAT 1
#define LUNGE 2
#define ADVANCE_LUNGE 3
#define FLECHE 4

// Set definitions for LED strip
#define NUM_LEDS 110
#define NUM_LEDS_PER_METER 30
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

// Define keypad
#include <Keypad.h>

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

  
  leds[x] = CRGB::Blue;
  for ( int i = 1; i <= r; i++ ) {
    leds[x-i] = CRGB( 255*(r-i)/r, 0, 0);
    leds[x+i] = CRGB( 255*(r-i)/r, 0, 0);
  }
  FastLED.show();
  FastLED.delay(5);
}

void setMode(){
  char key = keypad.getKey();
  switch(key) {
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
    default:
      break;
  }
}

void move (int moveType, int speed, int start) {
  switch(moveType) {
    case ADVANCE:
      break;
    case RETREAT:
      break;
    case LUNGE:
      break;
    case ADVANCE_LUNGE:
      break;
    case FLECHE:
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
  switch(mode) {
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
      position(0, 2);         // end
      position(NUM_LEDS/2, 2); // middle
      position(NUM_LEDS, 2);   // start
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
    case RANDOM_SLOW:
      break;
    case RANDOM_QUICK:
      break;
    default:
      break;
  }
}
