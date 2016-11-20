
/*
 * 
 * 
 * 
 */

#include "Balestra.h"

Balestra buddy;

void setup() {
  delay(2000);
}

void loop() {
  buddy.setMode(buddy.getKey());
  
  switch(buddy.getMode()) {
    case SETUP:
	  buddy.fill(CRGB::Blue);
      break;
    case SHUTTLE:
	  buddy.position(buddy.convertToLEDs(0.10);
	  buddy.position(buddy.convertToLEDs(2.00);
	  buddy.position(buddy.convertToLEDs(3.80);
      break;
    case RANDOM:
      break;
    case TRAINING_LOOP_3A_3R:
      break;
    case TRAINING_LOOP_L_R:
      break;
    default:
      break;
  }
}
