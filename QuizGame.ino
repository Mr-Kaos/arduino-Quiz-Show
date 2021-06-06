#include "Player.h"
#include "Arduino.h"
// #include "ButtonOrder.h"
#include "Game.h"
//#include "arduino-timer.h"

//auto timer = timer_create_default();
boolean anyButtonPressed = false;
boolean gameRunning = false;
boolean stopReset = false;
int masterSwitch = 7;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Player initialisation.
// Parameters: Player Number, LED pin, Button Pin, LED state, was their button pressed, score.
Player* p1 = new Player (1, 9,  2, LOW, NOT_PRESSED, 0);
Player* p2 = new Player (2, 10, 3, LOW, NOT_PRESSED, 0);
Player* p3 = new Player (3, 11, 4, LOW, NOT_PRESSED, 0);
Player* p4 = new Player (4, 12, 5, LOW, NOT_PRESSED, 0);

//ButtonOrder* pressOrder = new ButtonOrder;
// Array to store button press order
int pressPosition = 0;
Player* tmpPointer = nullptr;
Player* pressOrder[MAX_PLAYERS];

void setup()
{
    clearPressOrder();

    // Master user initialisation
    pinMode(masterSwitch, INPUT); // Master Button

    assignPin(p1);
    assignPin(p2);
    assignPin(p3);
    assignPin(p4);
    
    Serial.begin(9600);
        while (!Serial) {
    }

    // Piezo speaker setup

}

void assignPin(Player* player) {
    pinMode(player->getPinLED(), OUTPUT);    //LED
    pinMode(player->getPinBtn(), INPUT);     //button
}

void loop() {
    
    // PLAYER BUTTONS
    if (digitalRead(p1->getPinBtn()) == LOW) {
        buttonPress(p1);
    } else {
        //digitalWrite((p1->getPinLED()), LOW);
    }

    if (digitalRead(p2->getPinBtn()) == LOW) {
        // Serial.println("P2");
        // if (p2->getLEDState() == LOW) {
        //     if (!anyButtonPressed) {
        //         p2->setLEDState(HIGH);
        //     }
        //     if (!p2->wasButtonPressed()) {
        //         pressOrder[pressPosition] = p2;
        //         pressPosition++;
        //         p2->setButtonPressed(true);
        //         Serial.println("Added p2 to collection");
        //     }
        //     // pressOrder[pressPosition] = p2;
        //     // pressPosition++;
        //     // //pressOrder->addElement(p2);
        //     // Serial.println("Added p2 to collection");
        //     anyButtonPressed = true;
        // }
        // digitalWrite((p2->getPinLED()), p2->getLEDState());
        buttonPress(p2);
    } else {
        //digitalWrite((p2->getPinLED()), LOW);
    }

    if (digitalRead(p3->getPinBtn()) == LOW) {
        buttonPress(p3);
    } else {
        //digitalWrite((p2->getPinLED()), LOW);
    }

    if (digitalRead(p4->getPinBtn()) == LOW) {
        buttonPress(p4);
    } else {
        //digitalWrite((p2->getPinLED()), LOW);
    }

    // MASTER CONTROL
    // reset LEDS
    if (digitalRead(masterSwitch) == HIGH && !stopReset) {
        Serial.println("MASTER SWITCH");
        for (int i = 0; i < MAX_PLAYERS; ++i) {
            Serial.print("PLAYER: ");
            Serial.println(pressOrder[i]->getID());
            digitalWrite(pressOrder[i]->getPinLED(), pressOrder[i]->getLEDState());
        }
        stopReset = true;
    }
    else if (digitalRead(masterSwitch) == LOW && stopReset) {
        Serial.println("Master switch is off and the game is to be reset!");
        // reset button press array
        clearPressOrder();
        anyButtonPressed = false;

        p1->setButtonPressed(false);
        p2->setButtonPressed(false);
        p3->setButtonPressed(false);
        p4->setButtonPressed(false);
        digitalWrite(p1->getPinLED(), p1->getLEDState());
        digitalWrite(p2->getPinLED(), p2->getLEDState());
        digitalWrite(p3->getPinLED(), p3->getLEDState());
        digitalWrite(p4->getPinLED(), p4->getLEDState());
        pressPosition = 0;
        stopReset = false;
    }
}

void buttonPress(Player* player) {
    Serial.print("Player ");
    Serial.println(player->getID());
    if (player->getLEDState() == LOW) {
        if (!anyButtonPressed) {
            player->setLEDState(HIGH);
        }
        // Check if the player's button was alread pressed. If it was, do not add it to the array of button presses again.
        if (!player->wasButtonPressed()) {
            pressOrder[pressPosition] = player;
            pressPosition++;
            player->setButtonPressed(true);
            Serial.print("Added player ");
            Serial.print(player->getID());
            Serial.println(" to collection.");
        }
        anyButtonPressed = true;
    }
    digitalWrite((player->getPinLED()), player->getLEDState());
}

void clearPressOrder() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        pressOrder[i]->setLEDState(LOW);
        pressOrder[i] = tmpPointer;
    }
}