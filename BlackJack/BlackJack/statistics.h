#pragma once
#include <vector>
#include <string>
#include "Player.h"

void saveStatsToCSV(const std::vector<Player*>& players, const std::string& filename);
