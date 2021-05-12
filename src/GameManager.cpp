//
// Created by Michael Hodge on 5/10/21.
//

#include "GameManager.h"

GameManager::GameManager() {

    // Create the players - 1 human and 3 computer
    CreatePlayers();
    // Create a deck
    GameDeck = new Deck();
    // Deal hands to the players
    DealHandsToPlayers();
    // Draw the first card
    DrawFirstCard();

    Players[0]->StartTurn(this);
}

GameManager::~GameManager() {
    // Destroy players
    DestroyPlayers();
    // Destroy deck
    delete GameDeck;
}

void GameManager::CreatePlayers() {
    for(int i = 0; i < 4; i++)
    {
        if(i == 0)
            Players[i] = new Player(true);
        else
            Players[i] = new Player(false);
    }
}

void GameManager::DestroyPlayers() {
    for(auto player : Players)
        delete player;
}

void GameManager::DrawFirstCard() {
    // Draw the first card at the start of the game
    Card* PulledCard = GameDeck->DrawCard();
    // Place card in the card stack
    CardStack.push_back(PulledCard);
    std::cout << "The first card is " << PulledCard->CardColor << ", " << PulledCard->CardValue << std::endl;
}

Card* GameManager::DrawCard() {
    // Recycle the cards if there are no cards in the card stack
    if (GameDeck->Cards.size() <= 0)
    {
        RecycleCards();
    }
    // Draw a card
    Card* card = GameDeck->DrawCard();
    return card;
}

void GameManager::RecycleCards() {
    // Move all cards from card stack into game deck
    for(int i = 0; i < CardStack.size(); i++)
    {
        GameDeck->Cards.push_back(CardStack[i]);
        CardStack.erase(CardStack.begin() + i);
    }
    // Shuffle the cards
    GameDeck->ShuffleDeck();
}

void GameManager::DealHandsToPlayers() {
    int cardIndex = 0;
    for(int i = 0; i < sizeof Players / sizeof Players[0]; i++)
    {
        // Create hand
        std::vector<Card*> NewHand;
        for(int j = 0; j < 7; j++)
        {
            // Assign card to the player hand
            NewHand.push_back(GameDeck->Cards[cardIndex]);
            // Remove the card from the deck
            GameDeck->Cards.erase(GameDeck->Cards.begin() + cardIndex);
            cardIndex++;
        }
        // deal hand to player
        Players[i]->DealHand(NewHand);
    }
}

bool GameManager::PlaceCard(Player *player, Card *placedCard) {

    if (placedCard->CardColor ==  CardStack[CardStack.size() - 1]->CardColor || placedCard->CardValue  == CardStack[CardStack.size() - 1]->CardValue)
    {
        CardStack.push_back(placedCard);
        std::cout << "A card was Placed! " << CardStack[CardStack.size() - 1]->CardColor << ", " << CardStack[CardStack.size() - 1]->CardValue << std::endl;
        return true;
    }
    else
        return false;

}

void GameManager::PlayerFinishedTurn() {

};