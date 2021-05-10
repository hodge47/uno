#include <iostream>
#include "Card.h"
#include "Deck.h"

int main() {

    Deck* myDeck = new Deck();
    myDeck->ShuffleDeck();
    myDeck->PrintDeckCards();
    delete myDeck;


    return 0;
}
