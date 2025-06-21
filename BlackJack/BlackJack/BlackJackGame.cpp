#include "BlackJackGame.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "Player.h"

void saveStatsToCSV(const std::vector<Player*>& players, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << "\n";
        return;
    }

  
    file << "Name,Wins,Losses,Pushes,Total Earnings,Current Balance\n";

  
    for (const auto& player : players) {
        file << player->getName() << ','
            << player->getWins() << ','
            << player->getLosses() << ','
            << player->getPushes() << ','
            << player->getTotalEarnings() << ','
            << player->getBalance() << '\n';
    }

    file.close();
    std::cout << "Player statistics saved to " << filename << std::endl;
}
