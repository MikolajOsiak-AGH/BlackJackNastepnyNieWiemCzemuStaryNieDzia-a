#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Card.h"

using namespace std;
class Hand {
private:
    vector<Card> cards;
public:
    void addCard(Card card) { cards.push_back(card); }
    int getTotal() const {
        int total = 0, aceCount = 0;
        for (auto& card : cards) {
            total += card.getValue();
            if (card.getValue() == 11) aceCount++;
        }
        while (total > 21 && aceCount--) total -= 10;
        return total;
    }
    bool isBust() const { return getTotal() > 21; }
    void showHand(bool hideFirstCard = false) const {
        const int CARD_WIDTH = 9;
        vector<string> lines[7];

        for (size_t i = 0; i < cards.size(); ++i) {
            if (i == 0 && hideFirstCard) {
                lines[0].push_back("+-------+");
                lines[1].push_back("|*******|");
                lines[2].push_back("|*******|");
                lines[3].push_back("|*******|");
                lines[4].push_back("|*******|");
                lines[5].push_back("|*******|");
                lines[6].push_back("+-------+");
            }
            else {
                string rank = cards[i].getRank();
                string suit = cards[i].getSuitSymbol();

                string top = "|" + rank + string(7 - rank.length(), ' ') + "|";
                string bottom = "|" + string(7 - rank.length(), ' ') + rank + "|";

                lines[0].push_back("+-------+");
                lines[1].push_back(top);
                lines[2].push_back("|       |");
                lines[3].push_back("|   " + suit + "   |");
                lines[4].push_back("|       |");
                lines[5].push_back(bottom);
                lines[6].push_back("+-------+");
            }
        }

        for (int row = 0; row < 7; ++row) {
            for (const auto& part : lines[row]) {
                cout << part << " ";
            }
            cout << endl;
        }

        
        if (!hideFirstCard) {
            int total = getTotal();
            string reset = "\033[0m";
            string red = "\033[1;31m";
            string green = "\033[1;32m";

            if (isBust()) {
                cout << red << "BUSTED (Total: " << total << ")" << reset << endl;
            }
            else if (total == 21 && cards.size() == 2) {
                cout << green << "BLACKJACK!" << reset << endl;
            }
            else {
                cout << "Total: " << total << endl;
            }
        }
    }

    void clear() { cards.clear(); }
    bool isSplittable() const {
        return cards.size() == 2 && cards[0].getRank() == cards[1].getRank();
    }
    Card removeCard() {
        Card temp = cards.back();
        cards.pop_back();
        return temp;
    }
    const vector<Card>& getCards() const {
        return cards;
    }
};
