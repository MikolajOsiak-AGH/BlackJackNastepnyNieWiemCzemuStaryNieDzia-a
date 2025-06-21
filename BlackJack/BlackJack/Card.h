#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;
class Card {
private:
    string suit;
    string rank;
    int value;
public:
    Card(string r, string s) : rank(r), suit(s) {
        if (r == "A") value = 11;
        else if (r == "K" || r == "Q" || r == "J") value = 10;
        else value = stoi(r);
    }
    int getValue() const { return value; }
    string toString() const { return rank + " of " + suit; }
    string getRank() const { return rank; }
    string getSuitSymbol() const {
        string reset = "\033[0m";
        string red = "\033[31m";

        if (suit == "Hearts")   return red + "H" + reset;
        if (suit == "Diamonds") return red + "D" + reset;
        if (suit == "Clubs")    return "C";
        if (suit == "Spades")   return "S";
        return "?";
    }
};