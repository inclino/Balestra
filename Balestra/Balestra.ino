
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
      break;
    case SHUTTLE:
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
