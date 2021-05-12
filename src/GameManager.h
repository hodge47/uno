//
// Created by Michael Hodge on 5/10/21.
//

#ifndef UNO_GAMEMANAGER_H
#define UNO_GAMEMANAGER_H

#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

class GameManager {
private:
    class Player* Players [4] {};
    int PlayerTurn;
    bool Winner = false;
    Deck* GameDeck;
    std::vector<Card*> CardStack;

    void DealHandsToPlayers();
public:
    GameManager();
    ~GameManager();
    void CreatePlayers();
    void DestroyPlayers();
    void DrawFirstCard();
    Card* DrawCard();
    void RecycleCards();
    bool PlaceCard(class Player* player, Card* placedCard);
    void PlayerFinishedTurn(Player* player);
    void PlayerWon(class Player* player);
    void ShowTopOfCardStack();
};


#endif //UNO_GAMEMANAGER_H
