//
// Created by Michael Hodge on 5/10/21.
//

#include <iostream>
#include "Deck.h"

Deck::Deck() {
    // Create the deck
    CreateDeck();
}

Deck::~Deck() {
    // Destroy the deck
    DestroyDeck();
}

void Deck::CreateDeck()
{
    std::cout << "Creating deck..." << std::endl;
    int cardIndex = 0;
    // For each color, create cards 0-9 two times
    for(int i = 0; i < Card::Color::COLOR_COUNT; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            int cardValue = j;
            if(j > 9)
                cardValue = j - 10;
            Cards[cardIndex] = new Card((Card::Color)i, (Card::Value)cardValue);
            cardIndex++;
        }
    }
    std::cout << "Finished creating deck..." << std::endl;
}

/* Fisher-Yates Shuffle
 * Yoinked from https://gist.github.com/sundeepblue/10501662
 * My port from my C# implementation was not working for some reason
 */
void Deck::ShuffleDeck() {
    std::cout << "Shuffling deck..." << std::endl;
    int N = sizeof Cards / sizeof Cards[0];
    for(int i=N-1; i>0; --i) {
        int r = rand() % (i+1);
        // generate rand numbers from 0 to i
        std::swap(Cards[i], Cards[r]);
    }
}

void Deck::DestroyDeck() {
    for (auto card : Cards) {
        delete card;
    }
}

void Deck::PrintDeckCards() {
    int count = 0;
    for(auto card : Cards)
    {
        std::cout << "Card color: " << card->CardColor << ", Card value: " << card->CardValue << std::endl;
        count++;
    }
    std::cout << "Card count: " << count << std::endl;
}