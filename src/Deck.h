//
// Created by Michael Hodge on 5/10/21.
//

#ifndef UNO_DECK_H
#define UNO_DECK_H
#include "Card.h"

class Deck {

private:
    Card* Cards [80] {};

    void CreateDeck();
    void DestroyDeck();

public:
    Deck();
    ~Deck();

    void ShuffleDeck();
    void PrintDeckCards();
};


#endif //UNO_DECK_H
