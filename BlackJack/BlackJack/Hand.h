#pragma once

#include <vector>
#include "Card.h"

class Hand {
private:
    std::vector<Card> cards;

public:
    void addCard(Card card);
    int getTotal() const;
    bool isBust() const;
    void showHand(bool hideFirstCard = false) const;
    void clear();
    bool isSplittable() const;
    Card removeCard();
    const std::vector<Card>& getCards() const;
};
