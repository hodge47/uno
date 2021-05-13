//
// Created by Michael Hodge on 5/10/21.
//

#ifndef UNO_GAMEMANAGER_H
#define UNO_GAMEMANAGER_H

#include <vector>
#include <algorithm>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

class GameManager {
private:
    std::vector<class Player*> Players;
    int PlayerTurn;
    bool Winner = false;
    Deck* GameDeck;
    std::vector<Card*> CardStack;
    Card::Color PickedCardColor = (Card::Color)0;
    bool MustMatchCardColorThisTurn = false;

    void DealHandsToPlayers();
    Card::Color ChooseRandomColor();
public:
    GameManager();
    ~GameManager();
    void CreatePlayers();
    void DestroyPlayers();
    void DrawFirstCard();
    Card* DrawCard();
    void RecycleCards();
    bool PlaceCard(class Player* player, Card* placedCard);
    void CheckForSpecialCard(Card* placedCards);
    void PlayerFinishedTurn(Player* player);
    void PlayerWon(class Player* player);
    void ShowTopOfCardStack();
};


#endif //UNO_GAMEMANAGER_H
