#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include "BlackJackGame.h"
#include "Player.h"
#include "statistics.h"

using namespace std;
int main() {
    system("chcp 65001 > nul");
    srand(time(0));
    int numPlayers;
    while (true) {
        cout << "Enter number of human players: ";
        if (cin >> numPlayers && numPlayers >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        else {
            cout << "Invalid input. Please enter a non-negative number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    BlackjackGame game;
    for (int i = 0; i < numPlayers; ++i) {
        string name;
        cout << "Enter name for player " << i + 1 << ": ";
        getline(cin, name);
        game.addPlayer(new Player(name, 1000));
    }

    int numAIs;
    while (true) {
        cout << "Enter number of AI players: ";
        if (cin >> numAIs && numAIs >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        else {
            cout << "Invalid input. Please enter a non-negative number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    for (int i = 0; i < numAIs; ++i) {
        game.addPlayer(new AIPlayer("AI_Player_" + to_string(i + 1), 1000));
    }

    do {
        game.playRound();
        game.displayStatisticsTable();
    } while (game.askReplay());


    saveStatsToCSV(game.getPlayers(), "player_stats.csv");
    cout << "Thanks for playing!\n";
  
    return 0;
}
