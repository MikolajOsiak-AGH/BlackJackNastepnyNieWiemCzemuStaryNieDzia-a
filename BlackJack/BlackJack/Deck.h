#pragma once

#include <vector>
#include "Card.h"

class Deck {
private:
    std::vector<Card> cards;
    int currentIndex;

public:
    Deck();
    void init(int numberOfDecks = 6);
    void shuffle();
    Card dealCard();
};
