//
// Created by Michael Hodge on 5/10/21.
//

#ifndef UNO_PLAYER_H
#define UNO_PLAYER_H

#include <iostream>
#include <vector>
#include "Card.h"
#include "GameManager.h"

class Player {

private:
    bool IsHuman;
    std::vector<Card*> Hand;
    int GetPlayerInput();

public:
    Player(bool ishuman);
    void DealHand(std::vector<Card*> newHand);
    std::vector<Card*> GetHand();
    void StartTurn(class GameManager* gameManager);
    void TryPlaceCard(class GameManager* gameManager);
    void DrawCard(Card* card);
    void FinishTurn(class GameManager* gameManager);
};


#endif //UNO_PLAYER_H
