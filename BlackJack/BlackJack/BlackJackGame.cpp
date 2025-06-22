#include "BlackjackGame.h"
#include "AIplayer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <thread>
#include <chrono>
using namespace std;

void BlackjackGame::removeBrokePlayers() {
    players.erase(remove_if(players.begin(), players.end(),
        [](Player* p) { return p->getBalance() <= 0; }),
        players.end());
}

void BlackjackGame::placeBets() {
    for (auto player : players) {
        double bet = 100;

        if (!player->isAI()) {
            string input;
            int intBet;

            while (true) {
                cout << "\n" << player->getName() << "'s Balance: $" << player->getBalance() << ". Enter bet: ";
                getline(cin, input);

                input.erase(0, input.find_first_not_of(" \t"));
                input.erase(input.find_last_not_of(" \t") + 1);

                stringstream ss(input);
                if (ss >> intBet && intBet > 0 && ss.eof()) {
                    if (player->placeBet(intBet)) {
                        break;
                    }
                    else {
                        cout << "Insufficient balance. ";
                    }
                }
                else {
                    cout << "Invalid input. Please enter a positive whole number.\n";
                }
            }
        }
        else {
            bet = 50 + rand() % 151;
            player->placeBet(bet);
            cout << player->getName() << " (AI) bets $" << bet << endl;
        }
    }
}

BlackjackGame::~BlackjackGame() {
    for (auto p : players) delete p;
}

void BlackjackGame::addPlayer(Player* player) {
    players.push_back(player);
}

const std::vector<Player*>& BlackjackGame::getPlayers() const {
    return players;
}

void BlackjackGame::displayStatisticsTable() const {
    cout << "\n=== Game Statistics ===\n";
    cout << left << setw(12) << "Name"
        << setw(8) << "Wins"
        << setw(8) << "Losses"
        << setw(8) << "Pushes"
        << setw(18) << "Total Earnings"
        << setw(10) << "Balance"
        << setw(10) << "Win Rate" << endl;

    cout << string(74, '-') << endl;

    for (auto player : players) {
        int wins = player->getWins();
        int losses = player->getLosses();
        int pushes = player->getPushes();
        int totalGames = wins + losses + pushes;

        double winRate = (totalGames > 0) ? (100.0 * wins / totalGames) : 0.0;

        cout << left << setw(12) << player->getName()
            << setw(8) << wins
            << setw(8) << losses
            << setw(8) << pushes
            << setw(18) << (player->getTotalEarnings() >= 0 ? "+" : "") + to_string((int)player->getTotalEarnings())
            << "$" << fixed << setprecision(2) << setw(9) << player->getBalance()
            << fixed << setprecision(1) << winRate << "%" << endl;
    }

    cout << string(74, '-') << "\n";
}

void BlackjackGame::playRound() {
    const bool WAIT_FOR_ENTER = false;

    dealer.resetHand();
    removeBrokePlayers();

    if (players.empty()) {
        cout << "All players are out of money. Game over.\n";
        exit(0);
    }

    if (players.size() == 1 && players[0]->getBalance() <= 0) {
        cout << players[0]->getName() << " is out of money. Game over.\n";
        exit(0);
    }

    deck.shuffle();

    for (auto player : players)
        player->resetHands();

    placeBets();

    for (auto player : players) player->addCard(0, deck.dealCard());
    dealer.getHand().addCard(deck.dealCard());
    for (auto player : players) player->addCard(0, deck.dealCard());
    dealer.getHand().addCard(deck.dealCard());

    cout << "\nDealer's Hand:\n";
    dealer.getHand().showHand(true);

    // FIX: insurance based on dealer's visible card (second card shown)
    std::string rank = dealer.getHand().getCards()[1].getRank();
    rank.erase(remove_if(rank.begin(), rank.end(), ::isspace), rank.end());
    std::transform(rank.begin(), rank.end(), rank.begin(), ::toupper);

    if (rank == "A") {
        for (auto player : players) {
            if (!player->isAI()) {
                cout << player->getName() << ", want insurance? (y/n): ";
                char ins;
                cin >> ins;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (ins == 'y') player->insure(player->getBalance() / 10);
            }
        }
    }

    if (dealer.getHand().getTotal() == 21) {
        cout << "\nDealer has Blackjack!\n";
        for (auto player : players) player->winInsurance();
        return;
    }

    for (auto player : players) {
        if (!player->isAI()) {
            cout << "\n[Private] " << player->getName() << ", press Enter to begin your turn...";
            cin.sync();
            cin.get();

#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }

        cout << "\n-- " << player->getName() << "'s Turn --\n";

        for (size_t i = 0; i < player->getHands().size(); ++i) {
            bool firstMove = true;

            while (true) {
                cout << "\nHand " << i + 1 << ":\n";
                player->getHands()[i].showHand();

                if (player->getHands()[i].isBust()) {
                    cout << "Busted!\n";
                    break;
                }

                if (player->getHands()[i].getTotal() == 21) {
                    cout << "Blackjack! You stand automatically.\n";
                    break;
                }

                int opt = player->getMove(player->getHands()[i], dealer.getHand().getCards()[1]);

                if (opt == 1) {
                    player->addCard(i, deck.dealCard());
                    firstMove = false;
                }
                else if (opt == 2) {
                    break;
                }
                else if (opt == 3 && firstMove) {
                    player->doubleDown(i, deck.dealCard());
                    cout << "You chose to Double Down!\n";
                    cout << "Your updated hand:\n";
                    player->getHands()[i].showHand();
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    break;
                }
                else if (opt == 4 && firstMove) {
                    player->surrender(i);
                    cout << "You surrendered.\n";
                    break;
                }
                else {
                    cout << "Invalid option or not allowed after first move.\n";
                }
            }
        }

        if (!player->isAI()) {
            if (WAIT_FOR_ENTER) {
                cout << "\nTurn complete. Press Enter to continue...";
                cin.sync();
                cin.get();
            }
            else {
                cout << "\nTurn complete. Switching to next player in 8 seconds...";
                std::this_thread::sleep_for(std::chrono::seconds(8));
            }

#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }
    }

    dealer.play(deck);
    cout << "\nDealer's Hand:\n";
    dealer.getHand().showHand();
    int dealerTotal = dealer.getHand().getTotal();

    for (auto player : players) {
        for (size_t i = 0; i < player->getHands().size(); ++i) {
            if (player->getBet(i) == 0) {
                cout << "\n" << player->getName() << "'s Result for Hand " << i + 1 << ": You surrendered.\n";
                continue;
            }

            int playerTotal = player->getHands()[i].getTotal();
            cout << "\n" << player->getName() << "'s Result for Hand " << i + 1 << ": ";

            if (player->getHands()[i].isBust()) {
                cout << "You busted.\n";
                player->loseBet(i);
            }
            else if (dealer.getHand().isBust() || playerTotal > dealerTotal) {
                cout << "You win!\n";
                player->winBet(i);
            }
            else if (playerTotal < dealerTotal) {
                cout << "You lose.\n";
                player->loseBet(i);
            }
            else {
                cout << "Push.\n";
                player->pushBet(i);
            }
        }
    }
}

bool BlackjackGame::askReplay() const {
    cout << "\nPlay another round? (y/n): ";
    char ch;
    cin >> ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return ch == 'y' || ch == 'Y';
}
