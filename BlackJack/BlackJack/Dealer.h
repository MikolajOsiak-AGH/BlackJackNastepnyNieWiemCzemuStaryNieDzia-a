#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Hand.h"
#include "Deck.h"
using namespace std;

class Dealer {
private:
    Hand hand;
public:
    void play(Deck& deck) {
        while (hand.getTotal() < 17) {
            hand.addCard(deck.dealCard());
        }
    }
    Hand& getHand() { return hand; }
    void resetHand() { hand.clear(); }
};