#include "Player.h"
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

Player::Player(string n, double b) : name(n), balance(b), insuranceBet(0) {
    hands.push_back(Hand());
    bets.push_back(0);
}

Player::~Player() {}

string Player::getName() const {
    return name;
}

bool Player::placeBet(double amount) {
    if (amount > balance) return false;
    if (bets.empty()) bets.push_back(0);
    bets[0] = amount;
    balance -= amount;
    return true;
}

double Player::getBet(int idx) const {
    if (idx >= 0 && idx < bets.size()) {
        return bets[idx];
    }
    return 0.0;
}

void Player::winBet(int idx) {
    double winAmount = bets[idx] * 2;
    balance += winAmount;
    recordWin(bets[idx]);
}

void Player::loseBet(int idx) {
    recordLoss(bets[idx]);
}

void Player::pushBet(int idx) {
    balance += bets[idx];
    recordPush();
}

void Player::resetHands() {
    hands.clear();
    bets.clear();
    insuranceBet = 0;
    hands.push_back(Hand());
    bets.push_back(0);
}

void Player::addCard(int idx, Card card) {
    hands[idx].addCard(card);
}

vector<Hand>& Player::getHands() {
    return hands;
}

double Player::getBalance() const {
    return balance;
}

void Player::splitHand() {
    if (!hands[0].isSplittable() || balance < bets[0]) return;
    Card c = hands[0].removeCard();
    Hand newHand;
    newHand.addCard(c);
    hands.push_back(newHand);
    bets.push_back(bets[0]);
    balance -= bets[0];
    cout << "Split successful. Hands: " << hands.size() << ", Bets: " << bets.size() << endl;
}

void Player::doubleDown(int idx, Card card) {
    if (balance >= bets[idx]) {
        balance -= bets[idx];
        bets[idx] *= 2;
        hands[idx].addCard(card);
    }
}

void Player::insure(double amount) {
    if (amount <= balance) {
        insuranceBet = amount;
        balance -= amount;
    }
}

double Player::getInsuranceBet() const {
    return insuranceBet;
}

void Player::winInsurance() {
    balance += insuranceBet * 3;
}

void Player::surrender(int idx) {
    double refund = bets[idx] / 2;
    balance += refund;
    recordLoss(bets[idx] / 2);
    bets[idx] = 0;
}

bool Player::isAI() const {
    return false;
}

int Player::getMove(const Hand& hand, const Card& dealerCard) {
    int choice;
    cout << "1) Hit  2) Stand  3) Double Down  4) Surrender\nChoice: ";
    cin >> choice;
    return choice;
}

// ----- STATISTICS -----
void Player::recordWin(double amount) {
    wins++;
    totalEarnings += amount;
}

void Player::recordLoss(double amount) {
    losses++;
    totalEarnings -= amount;
}

void Player::recordPush() {
    pushes++;
}

void Player::showStatistics() const {
    cout << "\n--- Statistics for " << name << " ---\n";
    cout << "Wins: " << wins << "\n";
    cout << "Losses: " << losses << "\n";
    cout << "Pushes: " << pushes << "\n";
    cout << "Total Earnings: $" << totalEarnings << "\n";
    cout << "Current Balance: $" << balance << "\n";
    cout << "---------------------------\n";
}

int Player::getWins() const {
    return wins;
}

int Player::getLosses() const {
    return losses;
}

int Player::getPushes() const {
    return pushes;
}

double Player::getTotalEarnings() const {
    return totalEarnings;
}
