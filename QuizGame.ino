#include "Player.h"
#include "Arduino.h"
// #include "ButtonOrder.h"
#include "Game.h"
#include "PiezoTones.h"

boolean anyButtonPressed = false;
boolean gameRunning = false;
boolean stopReset = false;
int masterSwitch = 7;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Player initialisation.
// Parameters: Player Number, LED pin, Button Pin, LED state, was their button pressed, score.
Player* p1 = new Player (1, 8,  2, LOW, NOT_PRESSED, 0);
Player* p2 = new Player (2, 9, 3, LOW, NOT_PRESSED, 0);
Player* p3 = new Player (3, 10, 4, LOW, NOT_PRESSED, 0);
Player* p4 = new Player (4, 11, 5, LOW, NOT_PRESSED, 0);

// List of players to allow for easy looping for repetitive tasks
Player* playerList[MAX_PLAYERS] = {p1, p2, p3, p4};

//ButtonOrder* pressOrder = new ButtonOrder;
// Array to store button press order
int pressPosition = 0;
Player* tmpPointer = nullptr;
Player* pressOrder[MAX_PLAYERS];

// Piezo Melodies
unsigned long lastMelodyStart;
int buzzerPress[BUZZER_MELODY] = { NOTE_C4, NOTE_G3, NOTE_C4, NOTE_G3, NOTE_C4, NOTE_G3, NOTE_C4, NOTE_G3, NOTE_C4, NOTE_G3 };
int buzzerPressDuration[BUZZER_MELODY] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

void setup() {
    // assign pressOrder array with null pointers
    clearPressOrder();

    // Master user initialisation
    pinMode(masterSwitch, INPUT); // Master Button

    // Assign each player pins for their LEDs and buttons 
    for (Player* player : playerList) {
        assignPin(player);
    }
    
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
    }
    if (digitalRead(p2->getPinBtn()) == LOW) {
        buttonPress(p2);
    }
    if (digitalRead(p3->getPinBtn()) == LOW) {
        buttonPress(p3);
    }
    if (digitalRead(p4->getPinBtn()) == LOW) {
        buttonPress(p4);
    }

    // MASTER CONTROL
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

        // reset LEDS
        for (Player* player : playerList) {
            player->setButtonPressed(false);
            digitalWrite(player->getPinLED(), player->getLEDState());
        }
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
            playMelody(buzzerPress, buzzerPressDuration);
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

void playMelody(int melody[], int melodyDurations[]) {
    for (int note = 0; note < 10; ++note) {
        // int noteDuration = 1000 / melodyDurations[note];
        //tone(PIEZO_PIN, melody[note], noteDuration);
       
        noTone(PIEZO_PIN);
        Serial.println(melody[note]);
        if (millis() - lastMelodyStart >= 1000) {
            lastMelodyStart += 1000;
            tone(PIEZO_PIN, 500, 1000);
        }
    }
}