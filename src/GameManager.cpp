//
// Created by Michael Hodge on 5/10/21.
//

#include "GameManager.h"
#include <unistd.h>

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

        //std::cout << Players[i] << std::endl;
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

    if(MustMatchCardColorThisTurn == true && placedCard->CardColor == PickedCardColor)
    {
        CardStack.push_back(placedCard);
        std::cout << "Player[" << PlayerTurn << "] placed a " << CardStack[CardStack.size() - 1]->CardColor << ", " << CardStack[CardStack.size() - 1]->CardValue << "!" << std::endl;
        MustMatchCardColorThisTurn = false;
        return true;
    }
    else if ((placedCard->CardColor ==  CardStack[CardStack.size() - 1]->CardColor) || (placedCard->CardValue  == CardStack[CardStack.size() - 1]->CardValue) || (placedCard->CardValue == Card::Value::Wild) || (placedCard->CardValue == Card::Value::Wild_draw4))
    {
        CardStack.push_back(placedCard);
        std::cout << "Player[" << PlayerTurn << "] placed a " << CardStack[CardStack.size() - 1]->CardColor << ", " << CardStack[CardStack.size() - 1]->CardValue << "!" << std::endl;

        return true;
    }
    else
        return false;

}

void GameManager::CheckForSpecialCard(Card* placedCard) {
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
    }

    // Reverse card
    if(placedCard->CardValue == (Card::Value)11)
    {
        std::reverse(Players.begin(), Players.end());
        std::cout << "The turn order has been reversed!" << std::endl;
    }

    // Draw 2 card
    if(placedCard->CardValue == (Card::Value)12)
    {
        int nextPlayer;
        if(PlayerTurn < Players.size() - 1)
            nextPlayer = PlayerTurn + 1;
        else
            nextPlayer = 0;

        Card* card1 = DrawCard();
        Card* card2 = DrawCard();
        Players[nextPlayer]->DrawCard(card1);
        Players[nextPlayer]->DrawCard(card2);
        std::cout << "Player [" << nextPlayer << "] had 2 cards added to their hand!" << std::endl;
    }

    // Wild cards
    if(placedCard->CardValue == (Card::Value)13 || placedCard->CardValue == (Card::Value)14)
    {
        PickedCardColor = ChooseRandomColor();
        MustMatchCardColorThisTurn = true;

        if(placedCard->CardValue == (Card::Value)14)
        {
            int nextPlayer;
            if(PlayerTurn < Players.size() - 1)
                nextPlayer = PlayerTurn + 1;
            else
                nextPlayer = 0;

            for(int i = 0; i < 4; i++)
            {
                Card* newCard = DrawCard();
                Players[nextPlayer]->DrawCard(newCard);
            }
            std::cout << "Player [" << nextPlayer << "] had 4 cards added to their hand!" << std::endl;
        }

        MustMatchCardColorThisTurn = true;
        std::cout << "The set color is " << PickedCardColor << "!" << std::endl;
    }
}

Card::Color GameManager::ChooseRandomColor()
{
    srand(time(NULL));
     Card::Color color = (Card::Color)(rand() % Card::Color::COLOR_COUNT);
    return color;
}

void GameManager::PlayerFinishedTurn(Player* player) {
    // Check to see if the card was a special card
    Card* placedCard = CardStack[CardStack.size() - 1];
    CheckForSpecialCard(placedCard);
    // Check to see if the card is a special card
    if(PlayerTurn < Players.size() - 1)
    {
        PlayerTurn++;
    }
    else
        PlayerTurn = 0;

    // Sleep for half a second to simulate computers taking time
    usleep(0.5 * 1000000);
    // Start the player turn
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