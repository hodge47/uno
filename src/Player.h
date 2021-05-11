//
// Created by Michael Hodge on 5/10/21.
//

#ifndef UNO_PLAYER_H
#define UNO_PLAYER_H

#include <iostream>
#include <vector>
#include "Card.h"

class Player {

private:
    bool IsHuman;
    std::vector<Card*> Hand;

public:
    Player(bool ishuman);
    void DealHand(std::vector<Card*> newHand);
    std::vector<Card*> GetHand();
};


#endif //UNO_PLAYER_H
