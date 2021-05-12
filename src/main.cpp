#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "GameManager.h"

int main(int argc, char* argv[]) {

    // TODO: Do this right
    // Early exit for build server
    if(argc > 1 && argv[1])
    {
        return 0;
    }

    // Game
    GameManager* Manager = new GameManager();
    delete Manager;

    return 0;
}
