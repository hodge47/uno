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