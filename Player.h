#ifndef PLAYER
#define PLAYER
#include <Arduino.h>

class Player {

public:

    Player();
    ~Player();
    
    // modifiable vairables
    int score;
    boolean LEDState;

    Player (byte playerID, byte pinLED, byte pinBtn, boolean LEDState, int score);
    byte getPinLED();
    byte getPinBtn();
    byte getID();
    int getScore();
    boolean getLEDState();
    
    void setScore(int score);
    void setLEDState(boolean state);

// unmodifiable variables (created at startup.)
private:
    byte playerID;
    byte pinLED;
    byte pinBtn;
};

#endif //PLAYER
