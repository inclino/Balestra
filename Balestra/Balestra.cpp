#include <FastLED.h>
#include <Keypad.h>
#include "Balestra.h"

byte Balestra::getMode() { return mode; }
byte Balestra::getMovement() { return movement; }
void Balestra::setMovement(byte x) { movement = x; }
byte Balestra::getMovementSpeed() { return movementSpeed; }
void Balestra::setMovementSpeed(byte x) { movementSpeed = x; }
int Balestra::getMovementStart() { return movementStart; }
void Balestra::setMovementStart(int x) { movementStart = x; }

void Balestra::clear () {
  fill_solid( &(leds[0]), NUM_LEDS, CRGB::Black );
  FastLED.show();
}

void Balestra::fill (const struct CRGB &color) {
  fill_solid( &(leds[0]), NUM_LEDS, color );
  FastLED.show();
}

void Balestra::position ( int x, int r ) {
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

void Balestra::setMode (byte x) {
  // Set default speed
  setMovementSpeed(50);

  // Switch modes
  switch (x) {
    case 'A':
      mode = SETUP;
      break;
    case 'B':
      mode = SHUTTLE;
      break;
    case '1':
      mode = RANDOM;
      setMovementSpeed(10);
      break;
    case '2':
      mode = RANDOM;
      setMovementSpeed(20);
      break;
    case '3':
      mode = RANDOM;
      setMovementSpeed(30);
      break;
    case '4':
      mode = RANDOM;
      setMovementSpeed(40);
      break;
    case '5':
      mode = RANDOM;
      setMovementSpeed(50);
      break;
    case '6':
      mode = RANDOM;
      setMovementSpeed(60);
      break;
    case '7':
      mode = RANDOM;
      setMovementSpeed(70);
      break;
    case '8':
      mode = RANDOM;
      setMovementSpeed(80);
      break;
    case '9':
      mode = RANDOM;
      setMovementSpeed(90);
      break;
    case '0':
      mode = RANDOM;
      setMovementSpeed(100);
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

void Balestra::move () {
  // Initialize ending led variable
  int walk = movementStart;
  if ( walk > (NUM_LEDS - 30) ) { movement = RETREAT; }
  if ( walk < 30 ) { movement = ADVANCE; }
  
  // Set all leds to black
  clear();

  // Initialize speed recalculation (percentages to delays)
  if(movementSpeed < 10) { movementSpeed = 10; }
  int delayTime = map(movementSpeed, 10, 100, 1000, 25);
  
  // Start moving
  switch(movement) {
    case HOLDING:
      position(walk, 2);
      FastLED.delay(delayTime);
      break;
    case ADVANCE:
      position(walk, 2);
      FastLED.delay(delayTime);
      for(byte i = 1; i < 20; i++) {
        clear();
        position(walk + i, 2);
        FastLED.delay(5);
      }
      FastLED.delay(delayTime);
      walk += 19;
      break;
    case RETREAT:
      position(walk, 2);
      FastLED.delay(delayTime);
      for(byte i = 1; i < 20; i++) {
        clear();
        position(walk - i, 2);
        FastLED.delay(5);
      }
      FastLED.delay(delayTime);
      walk += -19;
      break;
    case LUNGE:
      position(walk, 2);
      FastLED.delay(delayTime);
      for(byte i = 1; i < 40; i++) {
        clear();
        position(walk + i, 2);
        FastLED.delay(5);
      }
      FastLED.delay(delayTime);
      walk += 39;
      break;
    case LUNGE_ENEMY:
      position(walk, 2);
      FastLED.delay(delayTime);
      for(byte i = 1; i < 40; i++) {
        clear();
        position(walk + i, 2);
        FastLED.delay(5);
      }
      FastLED.delay(delayTime);
      walk += 39;
      break;
    case ADVANCE_LUNGE:
      break;
    case FLECHE:
      break;
    default:
      break;
  }
  
  if ( walk < 0 ) { setMovementStart(0); }
  if ( walk > NUM_LEDS ) { setMovementStart(NUM_LEDS); }
  else { setMovementStart(walk); }
}

Balestra::Balestra () {
  delay(2000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);

  mode = SETUP;
  movementSpeed = 50;
  movement = HOLDING;
  movementStart = 20;
}

byte Balestra::getRandomMovement() {
  int randNumber = random(0,100);
  if ( randNumber < 30 ) { return HOLDING; }
  else if ( randNumber >= 30 && randNumber < 60 ) { return ADVANCE; }
  else if ( randNumber >= 60 && randNumber < 90 ) { return  RETREAT; }
  else { return LUNGE; }
}

byte Balestra::getKey() {
  return keypad.getKey();
}

int Balestra::convertToLEDs ( float m, byte offset = 0 ) {
  return m / NUM_LEDS_PER_METER + offset;
}

