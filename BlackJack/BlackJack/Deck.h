#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Card.h"
using namespace std;


class Deck {
private:
    vector<Card> cards;
    int currentIndex;
public:
    Deck() { init(); }
    void init(int numberOfDecks = 6) {
        cards.clear();
        string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
        for (int d = 0; d < numberOfDecks; ++d) {
            for (string s : suits) {
                for (string r : ranks) {
                    cards.push_back(Card(r, s));
                }
            }
        }
        shuffle();
    }
    void shuffle() {
        srand(time(0));
        random_shuffle(cards.begin(), cards.end());
        currentIndex = 0;
    }
    Card dealCard() {
        if (currentIndex >= cards.size()) {
            init();
        }
        return cards[currentIndex++];
    }
};