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

    // Start player turns
    PlayerTurn = 0;
    Players[PlayerTurn]->StartTurn(this);
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
            Players.push_back(new Player(true));
        else
            Players.push_back(new Player(false));

        std::cout << Players[i] << std::endl;
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
    //std::cout << "The first card is " << PulledCard->CardColor << ", " << PulledCard->CardValue << std::endl;
}

Card* GameManager::DrawCard() {
    // Recycle the cards if there are no cards in the card stack
    if (GameDeck->Cards.size() <= 0)
    {
        RecycleCards();
    }
    std::cout << "Player[" << PlayerTurn << "] drew a card!" << std::endl;
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
    for(int i = 0; i < Players.size(); i++)
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
        std::cout << "Player[" << PlayerTurn << "] placed a " << CardStack[CardStack.size() - 1]->CardColor << ", " << CardStack[CardStack.size() - 1]->CardValue << "!" << std::endl;

        return true;
    }
    else
        return false;

}

bool GameManager::CheckForSpecialCard(Card* placedCard) {
    //10 - skip, 11 - reverse, 12 - draw2

    // Skip the next player
    if(placedCard->CardValue == (Card::Value)10)
    {
        int playerCount = Players.size();

        int currentPlayer = PlayerTurn;
        int skippedPlayer;
        int nextPlayer;

        if(currentPlayer == playerCount - 1)
        {
            skippedPlayer = 0;
            nextPlayer = 1;
        }
        else
        {
            skippedPlayer = PlayerTurn++;
            nextPlayer = skippedPlayer++;
        }

        std::cout << "Player[" << skippedPlayer << "] was skipped!" << std::endl;
        std::cout << "It is now Player[" << nextPlayer << "]'s turn..." << std::endl;

        PlayerTurn = nextPlayer;
        return true;
    }

    // Reverse card
    if(placedCard->CardValue == (Card::Value)11)
    {
        std::reverse(Players.begin(), Players.end());
        std::cout << "The turn order has been reversed!" << std::endl;
    }

    return false;
}

void GameManager::PlayerFinishedTurn(Player* player) {
    // Check to see if the card is a special card
    if(CheckForSpecialCard(CardStack[CardStack.size() - 1]) == false)
    {
        if(PlayerTurn < Players.size() - 1)
        {
            PlayerTurn++;
        }
        else
            PlayerTurn = 0;
    }

    Players[PlayerTurn]->StartTurn(this);
};

void GameManager::PlayerWon(Player* player) {
    Winner = true;
    int PlayerIndex = -1;
    for(int i = 0; i < Players.size(); i++)
    {
        if(player == Players[i])
        {
            PlayerIndex = i;
            break;
        }
    }
    std::cout << "Player [" << PlayerIndex << "] Wins!" << std::endl;
}

void GameManager::ShowTopOfCardStack() {
    std::cout << "==============================================" << std::endl;
    for(int i = 0; i < Players.size(); i++)
    {
        if(Players[i]->GetIsHuman())
            std::cout << "Player[" << i << "](You) has " << Players[i]->GetHand().size() << " cards" << std::endl;
        else
            std::cout << "Player[" << i << "] has " << Players[i]->GetHand().size() << " cards" << std::endl;
    }
    std::cout << "Top of card stack: " << CardStack[CardStack.size() - 1]->CardColor << ", " << CardStack[CardStack.size() - 1]->CardValue << std::endl;
    std::cout << "==============================================" << std::endl;
}