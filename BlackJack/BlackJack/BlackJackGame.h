#pragma once
#include <vector>
#include <string>
#include "Deck.h"
#include "Dealer.h"
#include "Player.h"

class BlackjackGame {
private:
    Deck deck;
    std::vector<Player*> players;
    Dealer dealer;

    void removeBrokePlayers();
    void placeBets();

public:
    BlackjackGame() = default;
    ~BlackjackGame();

    void addPlayer(Player* player);
    void playRound();
    bool askReplay() const;
    void displayStatisticsTable() const;
    const std::vector<Player*>& getPlayers() const;
};
