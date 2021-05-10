//
// Created by Michael Hodge on 5/10/21.
//

#include "Player.h"

Player::Player(bool ishuman) {
    IsHuman = ishuman;
}

void Player::DealHand(Card *hand) {
    // Get the length needed for the hand vector
    int N = sizeof hand / sizeof hand[0];
    std::cout << "(Hand)===========================================" << std::endl;
    for(int i = 0; i < N; i++)
    {
        Hand.push_back(hand[i]);
        std::cout << "Card color: " << hand[i].CardColor << ", Card value: " << hand[0].CardValue << std::endl;
    }
}