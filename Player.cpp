#include "Player.h"

Player::Player(byte playerID, byte pinLED, byte pinBtn, boolean LEDState, int score) {
    this->playerID = playerID;
    this->pinLED = pinLED;
    this->pinBtn = pinBtn;
    this->LEDState = LEDState;
    this->score = score;
}

Player::Player() {
    // Contructor of player
}

Player::~Player() {
    // Deconstructor of player
    Serial.println("Player deleted");
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

void Player::setScore(int score) {
    this->score = score;
}

void Player::setLEDState(boolean state) {
    LEDState = state;
    //Serial.println(state);
}
