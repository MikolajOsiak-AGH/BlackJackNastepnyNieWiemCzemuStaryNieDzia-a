#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <limits>
#include "Card.h"
#include "Hand.h"

using namespace std;

class Player {
private:
    int wins = 0;
    int losses = 0;
    int pushes = 0;
    double totalEarnings = 0.0;

protected:
    string name;
    double balance;
    vector<Hand> hands;
    vector<double> bets;
    double insuranceBet;

public:
    Player(string n, double b) : name(n), balance(b), insuranceBet(0) {
        hands.push_back(Hand());
        bets.push_back(0);
    }

    virtual ~Player() {}

    string getName() const { return name; }

    virtual bool placeBet(double amount) {
        if (amount > balance) return false;
        if (bets.empty()) bets.push_back(0); // safety check
        bets[0] = amount;
        balance -= amount;
        return true;
    }

    double getBet(int idx) const {
        if (idx >= 0 && idx < bets.size()) {
            return bets[idx];
        }
        return 0.0;
    }

    void winBet(int idx) {
        double winAmount = bets[idx] * 2;
        balance += winAmount;
        recordWin(bets[idx]);
    }

    void loseBet(int idx) {
        recordLoss(bets[idx]);
    }

    void pushBet(int idx) {
        balance += bets[idx];
        recordPush();
    }

    void resetHands() {
        hands.clear();
        bets.clear();
        insuranceBet = 0;
        hands.push_back(Hand());
        bets.push_back(0);
    }

    void addCard(int idx, Card card) {
        hands[idx].addCard(card);
    }

    vector<Hand>& getHands() { return hands; }

    double getBalance() const { return balance; }

    void splitHand() {
        if (!hands[0].isSplittable() || balance < bets[0]) return;
        Card c = hands[0].removeCard();
        Hand newHand;
        newHand.addCard(c);
        hands.push_back(newHand);
        bets.push_back(bets[0]);
        balance -= bets[0];
        cout << "Split successful. Hands: " << hands.size() << ", Bets: " << bets.size() << endl;
    }

    void doubleDown(int idx, Card card) {
        if (balance >= bets[idx]) {
            balance -= bets[idx];
            bets[idx] *= 2;
            hands[idx].addCard(card);
        }
    }

    void insure(double amount) {
        if (amount <= balance) {
            insuranceBet = amount;
            balance -= amount;
        }
    }

    double getInsuranceBet() const { return insuranceBet; }

    void winInsurance() { balance += insuranceBet * 3; }

    void surrender(int idx) {
        double refund = bets[idx] / 2;
        balance += refund;
        recordLoss(bets[idx] / 2);
        bets[idx] = 0; // Mark as surrendered
    }

    virtual bool isAI() const { return false; }

    virtual int getMove(const Hand& hand, const Card& dealerCard) {
        int choice;
        cout << "1) Hit  2) Stand  3) Double Down  4) Surrender\nChoice: ";
        cin >> choice;
        return choice;
    }

    // ----- STATISTICS -----
    void recordWin(double amount) {
        wins++;
        totalEarnings += amount;
    }

    void recordLoss(double amount) {
        losses++;
        totalEarnings -= amount;
    }

    void recordPush() {
        pushes++;
    }

    void showStatistics() const {
        cout << "\n--- Statistics for " << name << " ---\n";
        cout << "Wins: " << wins << "\n";
        cout << "Losses: " << losses << "\n";
        cout << "Pushes: " << pushes << "\n";
        cout << "Total Earnings: $" << totalEarnings << "\n";
        cout << "Current Balance: $" << balance << "\n";
        cout << "---------------------------\n";
    }

    int getWins() const { return wins; }
    int getLosses() const { return losses; }
    int getPushes() const { return pushes; }
    double getTotalEarnings() const { return totalEarnings; }
};
