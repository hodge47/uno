//
// Created by Michael Hodge on 5/10/21.
//

#ifndef UNO_GAMEMANAGER_H
#define UNO_GAMEMANAGER_H

#include "Card.h"
#include "Deck.h"
#include "Player.h"

class GameManager {
private:
    Player* Players [4] {};
    Deck* GameDeck;

    void DealHandsToPlayers();
public:
    GameManager();
    ~GameManager();
    void CreatePlayers();
    void DestroyPlayers();
};


#endif //UNO_GAMEMANAGER_H
