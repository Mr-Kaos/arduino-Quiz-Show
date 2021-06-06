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
    boolean buttonPressed;

    Player (byte playerID, byte pinLED, byte pinBtn, boolean LEDState, boolean buttonPressed, int score);
    byte getPinLED();
    byte getPinBtn();
    byte getID();
    int getScore();
    boolean getLEDState();
    boolean wasButtonPressed();
    
    void setScore(int score);
    void setLEDState(boolean state);
    void setButtonPressed(boolean wasPressed);

// unmodifiable variables (created at startup.)
private:
    byte playerID;
    byte pinLED;
    byte pinBtn;
};

#endif //PLAYER
