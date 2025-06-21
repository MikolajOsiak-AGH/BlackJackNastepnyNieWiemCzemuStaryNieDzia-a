#include "Card.h"
#include <string>

Card::Card(std::string r, std::string s) : rank(r), suit(s) {
    if (r == "A") value = 11;
    else if (r == "K" || r == "Q" || r == "J") value = 10;
    else value = std::stoi(r);
}

int Card::getValue() const {
    return value;
}

std::string Card::toString() const {
    return rank + " of " + suit;
}

std::string Card::getRank() const {
    return rank;
}

std::string Card::getSuitSymbol() const {
    std::string reset = "\033[0m";
    std::string red = "\033[31m";

    if (suit == "Hearts")   return red + "H" + reset;
    if (suit == "Diamonds") return red + "D" + reset;
    if (suit == "Clubs")    return "C";
    if (suit == "Spades")   return "S";
    return "?";
}
