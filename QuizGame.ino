#include "Player.h"
#include "Arduino.h"
#include "ButtonOrder.h"
//#include "arduino-timer.h"

//auto timer = timer_create_default();
boolean buttonWasPressed = false;
boolean gameRunning = false;
boolean stopReset = false;
int masterSwitch = 7;

// Player initialisation.
// Parameters: Player Number, LED pin, Button Pin, LED state, score.
Player* p1 = new Player (1, 9, 2, LOW, 0);
Player* p2 = new Player (2, 10, 3, LOW, 0);
Player* p3 = new Player (3, 11, 4, LOW, 0);
Player* p4 = new Player (4, 12, 5, LOW, 0);

ButtonOrder* pressOrder = new ButtonOrder;

void setup()
{
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

    
    // if (Serial.available() > 0) {
    //     int debugInput = Serial.read();
    //     Serial.println(Serial.write(debugInput));
    //     if (debugInput == 'd') {
    //          Serial.print("Size of collection:");
    //          Serial.print(pressOrder->getPresses());
    //     }
    // }
    
    // PLAYER BUTTONS
    if (digitalRead(p1->getPinBtn()) == LOW) {
        Serial.println("P1");
        if (p1->getLEDState() == LOW && !buttonWasPressed) {
            if (!buttonWasPressed) {
                p1->setLEDState(HIGH);
            }
            pressOrder->addElement(p1);
            Serial.println("Added p1 to collection");
            buttonWasPressed = true;
        }
        digitalWrite((p1->getPinLED()), p1->getLEDState());
    } else {
        //digitalWrite((p1->getPinLED()), LOW);
    }

    if (digitalRead(p2->getPinBtn()) == LOW) {
        Serial.println("P2");
        if (p2->getLEDState() == LOW) {
            if (!buttonWasPressed) {
                p2->setLEDState(HIGH);
            }
            pressOrder->addElement(p2);
            Serial.println("Added p2 to collection");
            buttonWasPressed = true;
        }
        digitalWrite((p2->getPinLED()), p2->getLEDState());
    } else {
        //digitalWrite((p2->getPinLED()), LOW);
    }

    if (digitalRead(p3->getPinBtn()) == LOW) {
        Serial.println("P3");
        if (p3->getLEDState() == LOW) {
            if (!buttonWasPressed) {
                p3->setLEDState(HIGH);
            }
            pressOrder->addElement(p3);
            Serial.println("Added p3 to collection");
            buttonWasPressed = true;
        }
        digitalWrite((p3->getPinLED()), p3->getLEDState());
    } else {
        //digitalWrite((p2->getPinLED()), LOW);
    }

    // MASTER CONTROL
    // reset LEDS
//     if (digitalRead(masterSwitch) == HIGH && !stopReset) {
//         for (int i = 0; i < 4; ++i) {
//             Player* listPlayer = pressOrder->getPlayer(i);
//             listPlayer->setLEDState(LOW);
//             digitalWrite(listPlayer->getPinLED(), listPlayer->getLEDState());
//             Serial.println(listPlayer->getID());
//             if (i == 4) {
//                 stopReset == true;
//                 Serial.println("LIGHTS RESET!");
//             }
//         }
//     } else {
//         stopReset = false;
// //          Serial.println("Switch OFF");
//     }
}
