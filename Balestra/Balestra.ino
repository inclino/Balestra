#include "FastLED.h"

// Movement definitions
#define ADVANCE 0
#define RETREAT 1
#define LUNGE 2
#define ADVANCE_LUNGE 3
#define FLECHE 4

// Set definitions for LED strip
#define NUM_LEDS 30
#define NUM_LEDS_PER_METER 30
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

void clear () {
  fill_solid( &(leds[0]), NUM_LEDS, CRGB::Black );
  FastLED.show();
}

void position ( int x, int r, bool hb ) {
  // Fix over- and underflow
  if ( x - r < -1 ) {
    x = 0;
  } else if ( x + r >= NUM_LEDS ) {
    x = NUM_LEDS - r - 1;
  }

  if ( r <= 1 ) {
    r = 1;
  }

  // Heart beat animation
  if ( hb ) {
    leds[x] = CRGB::Red;
    for ( int i = 1; i <= r; i++ ) {
      leds[x-i] = CRGB( 255*(r-i)/r, 0, 0);
      leds[x+i] = CRGB( 255*(r-i)/r, 0, 0);
    }
  } else if ( !hb ) {
    leds[x] = CRGB::Red;
    for ( int i = 1; i <= r; i++ ) {
      leds[x-i] = CRGB( 255*(r-i)/r, 0, 0);
      leds[x+i] = CRGB( 255*(r-i)/r, 0, 0);
    }
  }
  FastLED.show();
  delay(25);
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
  // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
  for ( int i = 0; i < NUM_LEDS; i++ ) {
    position(i, 2, false);
    delay(25);
    clear();
  }
  
  for ( int i = NUM_LEDS; i > 0; i-- ) {
    position(i, 2, false);
    delay(25);
    clear();
  }
}
