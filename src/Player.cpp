//
// Created by Michael Hodge on 5/10/21.
//

#include "Player.h"

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