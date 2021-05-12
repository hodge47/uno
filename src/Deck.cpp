//
// Created by Michael Hodge on 5/10/21.
//

#include <iostream>
#include "Deck.h"

Deck::Deck() {
    // Create the deck
    CreateDeck();
    // Shuffle the deck
    ShuffleDeck();
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
        Cards.push_back(new Card((Card::Color)i, (Card::Value)0));
    }
    // For each color, create cards 1-13 two times
    for(int i = 0; i < Card::Color::COLOR_COUNT; i++)
    {
        for(int j = 1; j < 26; j++)
        {
            int cardValue = j;
            if(j > 12)
                cardValue = j - 13;
            Cards.push_back(new Card((Card::Color)i, (Card::Value)cardValue));
            cardIndex++;
        }
    }

    PrintDeckCards();
    std::cout << "Finished creating deck..." << std::endl;
}

/* Fisher-Yates Shuffle
 * Yoinked from https://gist.github.com/sundeepblue/10501662
 * My port from my C# implementation was not working for some reason
 */
void Deck::ShuffleDeck() {
    std::cout << "Shuffling deck..." << std::endl;
    int N = Cards.size();
    for(int i = N - 1; i > 0; --i) {
        srand (time(NULL));
        int r = rand() % (i+1);
        std::swap(Cards[i], Cards[r]);
    }
}

void Deck::DestroyDeck() {
    for (auto card : Cards) {
        delete card;
    }
}

Card* Deck::DrawCard(){
    srand (time(NULL));
    int RandomCard = rand() % (Cards.size() + 1);
    Card* PulledCard = Cards[RandomCard];
    // Remove the card from the deck
    Cards.erase(Cards.begin() + RandomCard);
    return PulledCard;
}

void Deck::PrintDeckCards() {
    int count = 0;
    for(int i = 0; i < Cards.size(); i++)
    {
        std::cout << "Card color: " << Cards[i]->CardColor << ", Card value: " << Cards[i]->CardValue << std::endl;
        count++;
    }
    std::cout << "Card count: " << count << std::endl;
}