#pragma once

#include <string>
#include <vector>
#include "Card.h"
#include "Hand.h"

class Player {
private:
    int wins = 0;
    int losses = 0;
    int pushes = 0;
    double totalEarnings = 0.0;

protected:
    std::string name;
    double balance;
    std::vector<Hand> hands;
    std::vector<double> bets;
    double insuranceBet;

public:
    Player(std::string n, double b);
    virtual ~Player();

    std::string getName() const;
    virtual bool placeBet(double amount);
    double getBet(int idx) const;

    void winBet(int idx);
    void loseBet(int idx);
    void pushBet(int idx);
    void resetHands();
    void addCard(int idx, Card card);
    std::vector<Hand>& getHands();
    double getBalance() const;

    void splitHand();
    void doubleDown(int idx, Card card);
    void insure(double amount);
    double getInsuranceBet() const;
    void winInsurance();
    void surrender(int idx);

    virtual bool isAI() const;
    virtual int getMove(const Hand& hand, const Card& dealerCard);

    void recordWin(double amount);
    void recordLoss(double amount);
    void recordPush();
    void showStatistics() const;

    int getWins() const;
    int getLosses() const;
    int getPushes() const;
    double getTotalEarnings() const;
};
