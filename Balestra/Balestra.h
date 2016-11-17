#ifndef Balestra_h
#define Balestra_h

#include <FastLED.h>
#include <Keypad.h>

// Keypad definitions
#define KP_ROWS 4
#define KP_COLS 4
#define KP_COL_PINS {5, 4, 3, 2}
#define KP_ROW_PINS {11, 10, 9, 8}
#define KP_KEYS {{'1','2','3','A'}, {'4','5','6','B'}, {'7','8','9','C'}, {'*','0','#','D'}}

// Mode definitions
#define SETUP 1
#define SHUTTLE 2
#define RANDOM 3
#define TRAINING_LOOP_3A_3R 4
#define TRAINING_LOOP_L_R 5

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

class Balestra {
  private:
    byte mode, movement, movementSpeed;
    int movementStart;
    CRGB leds[NUM_LEDS];

    char keys[KP_ROWS][KP_COLS] = KP_KEYS;
    byte rowPins[KP_ROWS] = KP_ROW_PINS;
    byte colPins[KP_COLS] = KP_COL_PINS; //connect to the column pinouts of the keypad
    Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, KP_ROWS, KP_COLS );

    void position ( int x, int r );
    void clear ();
  public:
    Balestra ();
    byte getKey();
    byte getMode();
    void setMode(byte x);
    byte getMovement();
    void setMovement(byte x);
    byte getMovementSpeed();
    void setMovementSpeed(byte x);
    int getMovementStart();
    void setMovementStart(int x);
    byte getRandomMovement ();
    void move ();
};

#endif
