#include "ButtonOrder.h"
#include "Arduino.h"

// Creator
ButtonOrder::ButtonOrder() {

}
// Deleter
ButtonOrder::~ButtonOrder() {
    // Serial.println("Deleted button order list");
}

int ButtonOrder::getPresses() {
    return this->presses;
}

Player* ButtonOrder::getPlayer(int i) {
    return buttons[i];
}

void ButtonOrder::addElement(Player* player) {
    buttons[presses] = player;
    presses++;
}

void ButtonOrder::clearList() {
    for (int i = 0; i < presses; i++) {
        delete buttons[i];
    }
}