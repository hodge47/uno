//
// Created by Michael Hodge on 5/10/21.
//

#include "GameManager.h"

GameManager::GameManager() {

    // Create the players - 1 human and 3 computer
    CreatePlayers();
    // Create a deck
    GameDeck = new Deck();
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

}