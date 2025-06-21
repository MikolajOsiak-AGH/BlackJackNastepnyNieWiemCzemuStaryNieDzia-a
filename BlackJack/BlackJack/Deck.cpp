#include "Deck.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

Deck::Deck() {
    init();
}

void Deck::init(int numberOfDecks) {
    cards.clear();
    std::string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    std::string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

    for (int d = 0; d < numberOfDecks; ++d) {
        for (const auto& s : suits) {
            for (const auto& r : ranks) {
                cards.emplace_back(r, s);
            }
        }
    }
    shuffle();
}

void Deck::shuffle() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::random_shuffle(cards.begin(), cards.end());
    currentIndex = 0;
}

Card Deck::dealCard() {
    if (currentIndex >= static_cast<int>(cards.size())) {
        init();
    }
    return cards[currentIndex++];
}
