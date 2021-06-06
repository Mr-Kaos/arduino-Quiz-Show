#include "Player.h"

Player::Player(byte playerID, byte pinLED, byte pinBtn, boolean LEDState, boolean buttonPressed, int score) {
    this->playerID = playerID;
    this->pinLED = pinLED;
    this->pinBtn = pinBtn;
    this->LEDState = LEDState;
    this->buttonPressed = buttonPressed;
    this->score = score;
}

Player::Player() {
    // Contructor of player
}

Player::~Player() {
    // Deconstructor of player
}

int Player::getScore() {
    return this->score;
}

byte Player::getPinBtn() {
    return this->pinBtn;
}

byte Player::getPinLED() {
    return this->pinLED;
}

byte Player::getID() {
    return this->playerID;
}

boolean Player::getLEDState() {
    return this->LEDState;
}

boolean Player::wasButtonPressed() {
    return this->buttonPressed;
}

void Player::setScore(int score) {
    this->score = score;
}

void Player::setLEDState(boolean state) {
    this->LEDState = state;
    //Serial.println(state);
}

void Player::setButtonPressed(boolean wasButtonPressed) {
    this->buttonPressed = wasButtonPressed;
}