#ifndef BUTTONORDER
#define BUTTONORDER

#include "Player.h"

class ButtonOrder {

public:
    ButtonOrder();
    ~ButtonOrder();

    int getPresses();

    // get a pointer to the i'th element in the list
    Player* getPlayer(int i);

    // add a player to the back of the list
    void addElement(Player* player);

    void clearList();

private:
    // List of buttons with a max size of 4 players
    Player* buttons[4];

    // Number of players who pressed their buttons
    int presses;
};


#endif