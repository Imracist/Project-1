#include "Pollution.h"
#include <iostream>

Pollution::Pollution(int width, int height) {
    pollutionMap = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
}

void Pollution::spreadPollution(int x, int y, int population) {
    pollutionMap[x][y] += population;
    // Spread pollution to adjacent cells
}

void Pollution::displayPollution() const {
    for (const auto& row : pollutionMap) {
        for (int p : row) {
            std::cout << p << " ";
        }
        std::cout << std::endl;
    }
}
