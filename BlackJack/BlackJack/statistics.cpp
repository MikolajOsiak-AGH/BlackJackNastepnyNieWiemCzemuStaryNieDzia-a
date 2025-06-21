#include <fstream>
#include "Player.h"
#include <vector>
#include <string>

void saveStatsToCSV(const std::vector<Player*>& players, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    file << "Name,Wins,Losses,Pushes,Total Earnings,Balance\n";

    for (const auto& player : players) {
        if (!player->isAI()) {
            file << player->getName() << ","
                << player->getWins() << ","       
                << player->getLosses() << ","     
                << player->getPushes() << ","     
                << player->getTotalEarnings() << ","
                << player->getBalance() << "\n";
        }
    }
}
