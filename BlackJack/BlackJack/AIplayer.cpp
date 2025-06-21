#include "AIPlayer.h"
#include <algorithm>

AIPlayer::AIPlayer(std::string n, double b)
    : Player(n, b) {
}

bool AIPlayer::placeBet(double amount) {
    amount = std::min(balance, 100.0);
    bets[0] = amount;
    balance -= amount;
    return true;
}

int AIPlayer::getMove(const Hand& hand, const Card& dealerCard) {
    int total = hand.getTotal();
    int dealerVal = dealerCard.getValue();

    if (total == 9 && dealerVal >= 3 && dealerVal <= 6) return 3;
    if (total == 10 && dealerVal >= 2 && dealerVal <= 9) return 3;
    if (total == 11 && dealerVal >= 2 && dealerVal <= 10) return 3;

    if (total <= 8) return 1;
    if (total == 9) return (dealerVal >= 3 && dealerVal <= 6) ? 3 : 1;
    if (total == 10) return (dealerVal <= 9) ? 3 : 1;
    if (total == 11) return 3;
    if (total >= 12 && total <= 16) return (dealerVal >= 2 && dealerVal <= 6) ? 2 : 1;

    return 2;
}

bool AIPlayer::isAI() const {
    return true;
}
