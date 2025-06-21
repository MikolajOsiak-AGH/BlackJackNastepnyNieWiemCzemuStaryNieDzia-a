#pragma once

#include <string>

class Card {
private:
    std::string suit;
    std::string rank;
    int value;

public:
    Card(std::string r, std::string s);

    int getValue() const;
    std::string toString() const;
    std::string getRank() const;
    std::string getSuitSymbol() const;
};
