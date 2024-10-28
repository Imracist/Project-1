#include "region.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool Region::readRegionFile(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) return false;

    std::string line;
    while (getline(file, line)) {
        std::vector<Cell> row;
        std::stringstream ss(line);
        std::string cellData;
        while (getline(ss, cellData, ',')) {
            Cell cell;
            cell.zoneType = cellData[0];
            row.push_back(cell);
        }
        grid.push_back(row);
    }
    return true;
}

void Region::simulateGrowth(int maxSteps, int refreshRate) {
    for (int step = 0; step < maxSteps; ++step) {
        bool populationChanged = false;
        std::vector<std::vector<Cell>> newPopulations = grid;

        int availableWorkers = calculateAvailableWorkers();
        int availableGoods = calculateAvailableGoods();

        for (size_t i = 0; i < grid.size(); ++i) {
            for (size_t j = 0; j < grid[i].size(); ++j) {
                Cell& cell = grid[i][j];

                // Residential Growth Rules
                if (cell.zoneType == 'R') {
                    int adjacentPowerline = isAdjacentTo(cell, 'T', 0, i, j);
                    int adjPop1 = isAdjacentTo(cell, 'R', 1, i, j);
                    int adjPop2 = isAdjacentTo(cell, 'R', 2, i, j);
                    int adjPop3 = isAdjacentTo(cell, 'R', 3, i, j);
                    int adjPop4 = isAdjacentTo(cell, 'R', 4, i, j);

                    if (cell.population == 0 && (adjacentPowerline > 0 || adjPop1 > 0)) {
                        newPopulations[i][j].population = 1;
                        populationChanged = true;
                    } else if (cell.population == 1 && adjPop1 >= 2) {
                        newPopulations[i][j].population = 2;
                        populationChanged = true;
                    } else if (cell.population == 2 && adjPop2 >= 4) {
                        newPopulations[i][j].population = 3;
                        populationChanged = true;
                    } else if (cell.population == 3 && adjPop3 >= 6) {
                        newPopulations[i][j].population = 4;
                        populationChanged = true;
                    } else if (cell.population == 4 && adjPop4 >= 8) {
                        newPopulations[i][j].population = 5;
                        populationChanged = true;
                    }
                }
                // Industrial Growth Rules
                else if (cell.zoneType == 'I') {
                    int adjacentPowerline = isAdjacentTo(cell, 'T', 0, i, j);
                    int adjPop1 = isAdjacentTo(cell, 'R', 1, i, j);

                    if (cell.population == 0 && adjacentPowerline > 0 && availableWorkers >= 2) {
                        newPopulations[i][j].population = 1;
                        availableWorkers -= 2;
                        populationChanged = true;
                    } else if (cell.population == 1 && adjPop1 >= 2 && availableWorkers >= 2) {
                        newPopulations[i][j].population = 2;
                        availableWorkers -= 2;
                        populationChanged = true;
                    } else if (cell.population == 2 && adjPop1 >= 4 && availableWorkers >= 2) {
                        newPopulations[i][j].population = 3;
                        availableWorkers -= 2;
                        populationChanged = true;
                    }
                }
                // Commercial Growth Rules
                else if (cell.zoneType == 'C') {
                    int adjacentPowerline = isAdjacentTo(cell, 'T', 0, i, j);
                    int adjPop1 = isAdjacentTo(cell, 'I', 1, i, j);

                    if (cell.population == 0 && adjacentPowerline > 0 && availableWorkers >= 1 && availableGoods >= 1) {
                        newPopulations[i][j].population = 1;
                        availableWorkers -= 1;
                        availableGoods -= 1;
                        populationChanged = true;
                    } else if (cell.population == 1 && adjPop1 >= 2 && availableWorkers >= 1 && availableGoods >= 1) {
                        newPopulations[i][j].population = 2;
                        availableWorkers -= 1;
                        availableGoods -= 1;
                        populationChanged = true;
                    }
                }
            }
        }

        // Update pollution based on industrial population
        for (size_t i = 0; i < grid.size(); ++i) {
            for (size_t j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j].zoneType == 'I' && newPopulations[i][j].population > 0) {
                    newPopulations[i][j].pollution += newPopulations[i][j].population; // Pollution from industrial cell
                }
            }
        }

        grid = newPopulations; // Update grid to the new population values

        printRegion(step); // Print the current state
        if (!populationChanged) {
            std::cout << "No change detected. Simulation ended." << std::endl;
            break;
        }

        // Wait for user input to proceed to the next step
        std::cout << "Press Enter to proceed to the next step, or 'q' to quit: ";
        std::string input;
        std::getline(std::cin, input);
        if (input == "q" || input == "Q") {
            std::cout << "Simulation stopped by user." << std::endl;
            break;
        }
    }

    // After simulation ends, output final totals
    outputFinalTotals();
}

void Region::outputFinalTotals() const {
    std::cout << "Final Region State Summary:" << std::endl;
    std::cout << "Total Residential Population: " << getTotalPopulation('R') << std::endl;
    std::cout << "Total Industrial Population: " << getTotalPopulation('I') << std::endl;
    std::cout << "Total Commercial Population: " << getTotalPopulation('C') << std::endl;
    std::cout << "Total Pollution in the Region: " << getTotalPollution() << std::endl;
}

void Region::printRegion(int step) const {
    std::cout << "Step " << step << "\n";
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.zoneType == 'I' && cell.pollution > 0) {
                std::cout << cell.population << "(" << cell.pollution << ") ";
            } else if (cell.population > 0) {
                std::cout << cell.population << " ";
            } else {
                std::cout << cell.zoneType << " ";
            }
        }
        std::cout << "\n";
    }
}

int Region::calculateAvailableWorkers() const {
    int availableWorkers = 0;
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.zoneType == 'R') {
                availableWorkers += cell.population;
            }
        }
    }
    return availableWorkers;
}

int Region::calculateAvailableGoods() const {
    int availableGoods = 0;
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.zoneType == 'I') {
                availableGoods += cell.population;
            }
        }
    }
    return availableGoods;
}

int Region::isAdjacentTo(const Cell& cell, char zoneType, int minPopulation, int x, int y) const {
    static const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    static const int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (newX >= 0 && newX < static_cast<int>(grid.size()) && newY >= 0 && newY < static_cast<int>(grid[0].size())) {
            const Cell& neighbor = grid[newX][newY];
            if (neighbor.zoneType == zoneType && neighbor.population >= minPopulation) {
                count++;
            }
        }
    }
    return count;
}

int Region::getTotalPopulation(char zoneType) const {
    int totalPopulation = 0;
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.zoneType == zoneType) {
                totalPopulation += cell.population;
            }
        }
    }
    return totalPopulation;
}

int Region::getTotalPollution() const {
    int totalPollution = 0;
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            totalPollution += cell.pollution; // Summing up pollution from each cell
        }
    }
    return totalPollution;
}

void Region::analyzeArea(int x1, int y1, int x2, int y2) const {
    if (x1 < 0 || y1 < 0 || x2 >= grid.size() || y2 >= grid[0].size() || x1 > x2 || y1 > y2) {
        std::cout << "Invalid coordinates." << std::endl;
        return;
    }

    int totalResidential = 0;
    int totalIndustrial = 0;
    int totalCommercial = 0;
    int totalPollution = 0;

    for (int i = x1; i <= x2; ++i) {
        for (int j = y1; j <= y2; ++j) {
            const Cell& cell = grid[i][j];
            if (cell.zoneType == 'R') {
                totalResidential += cell.population;
            } else if (cell.zoneType == 'I') {
                totalIndustrial += cell.population;
                totalPollution += cell.pollution;
            } else if (cell.zoneType == 'C') {
                totalCommercial += cell.population;
            }
        }
    }

    std::cout << "Analysis Results for the area (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << "):" << std::endl;
    std::cout << "Total Residential Population: " << totalResidential << std::endl;
    std::cout << "Total Industrial Population: " << totalIndustrial << std::endl;
    std::cout << "Total Commercial Population: " << totalCommercial << std::endl;
    std::cout << "Total Pollution: " << totalPollution << std::endl;
}
