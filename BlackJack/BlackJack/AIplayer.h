#pragma once
#include "Player.h"
#include "Card.h"
#include "Hand.h"

class AIPlayer : public Player {
public:
    AIPlayer(std::string n, double b);

    bool placeBet(double amount) override;
    int getMove(const Hand& hand, const Card& dealerCard) override;
    bool isAI() const override;
};
