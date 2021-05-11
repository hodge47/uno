//
// Created by Michael Hodge on 5/10/21.
//

#ifndef UNO_DECK_H
#define UNO_DECK_H
#include "Card.h"
#include <vector>

class Deck {

private:
    void CreateDeck();
    void DestroyDeck();

public:
    std::vector<Card*> Cards;

    Deck();
    ~Deck();

    void ShuffleDeck();
    void PrintDeckCards();
};


#endif //UNO_DECK_H
