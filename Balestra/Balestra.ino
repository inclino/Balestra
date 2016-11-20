
/*
 *  Balestra: your virtual fencing training partner
 *  by Inclino
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
      buddy.setMovement(buddy.getRandomMovement());
      buddy.move();
      break;
    case TRAINING_LOOP_3A_3R:
	  buddy.setMovementSpeed(20);
	  for ( byte i = 0; i < 3; i++ ) {
	    buddy.setMovement(ADVANCE);
	    buddy.move();
	  }
	  for ( byte i = 0; i < 3; i++ ) {
	    buddy.setMovement(RETREAT);
	    buddy.move();
	  }
      break;
    case TRAINING_LOOP_L_R:
	  buddy.setMovementSpeed(20);
      buddy.setMovement(LUNGE);
      buddy.move();
      buddy.setMovement(RETREAT);
      buddy.move();
      break;
    default:
      break;
  }
}
