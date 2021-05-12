//
// Created by Michael Hodge on 5/10/21.
//

#include "Player.h"
#include <string>
#include <sstream>

Player::Player(bool ishuman) {
    IsHuman = ishuman;
}

void Player::DealHand(std::vector<Card*> newHand) {
    // Get the length needed for the hand vector
    int N = newHand.size();
    for(int i = 0; i < N; i++)
    {
        Hand.push_back(newHand[i]);
    }
}

std::vector<Card*> Player::GetHand() {
    return Hand;
}

void Player::StartTurn(GameManager* gameManager) {

    if(IsHuman)
    {
        // Tell the player what their options are
        std::cout << "[Your Cards]" << std::endl;
        for(int i = 0; i < Hand.size(); i++)
        {
            std::cout << "[" << i << "] "<< Hand[i]->CardColor << ", " << Hand[i]->CardValue << std::endl;
        }
        std::cout << "[" << -1 << "] Draw Card" << std::endl;

        // Try to place card or draw card
        TryPlaceCard(gameManager);
    }
    else
    {
        // Iterate through cards and see if there is a match
        for(int i = 0; i < Hand.size(); i++)
        {
            if(gameManager->PlaceCard(this, Hand[i]) == true)
            {
                Hand.erase(Hand.begin() + i);
                FinishTurn(gameManager);
                return;
            }
        }

        // Draw card
        DrawCard(gameManager->DrawCard());
    }

}

int Player::GetPlayerInput() {
    std::string line;
    int option;
    std::cin >> option;

    return option;
}

void Player::TryPlaceCard(GameManager *gameManager) {
    if(IsHuman)
    {
        bool CanContinue = false;
        while(!CanContinue)
        {
            int option = GetPlayerInput();
            if(option == -1)
            {
                DrawCard(gameManager->DrawCard());
            }
            else
            {
                if (gameManager->PlaceCard(this, Hand[option]))
                {
                    Hand.erase(Hand.begin() + option);
                    CanContinue = true;
                }
            }


        }
    }

    FinishTurn(gameManager);
}

void Player::DrawCard(Card *card) {
    Hand.push_back(card);
    std::cout << "You drew a " << card->CardColor << ", " << card->CardValue << " card!" << std::endl;
}

void Player::FinishTurn(GameManager* gameManager) {

}