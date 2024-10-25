#include "region.h"
#include <fstream>
#include <iostream>
#include <sstream>

void Region::simulateGrowth() {
    std::vector<std::vector<Cell>> newPopulations = grid;  // Store new populations
    int availableWorkers = getAvailableWorkers();
    int availableGoods = getAvailableGoods();

    // Simulate growth for all zones
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            Cell& cell = grid[i][j];

            // Residential Growth
            if (cell.zoneType == 'R') {
                int adjacentRes = isAdjacentTo(cell, 'R', 1, i, j);
                int adjacentPowerline = isAdjacentTo(cell, 'T', 0, i, j);
                
                if (cell.population == 0 && (adjacentPowerline > 0 || adjacentRes > 0)) {
                    newPopulations[i][j].population = 1;
                } else if (cell.population == 1 && adjacentRes >= 2) {
                    newPopulations[i][j].population = 2;
                } else if (cell.population == 2 && adjacentRes >= 4) {
                    newPopulations[i][j].population = 3;
                } else if (cell.population == 3 && adjacentRes >= 6) {
                    newPopulations[i][j].population = 4;
                }
            }
            // Industrial Growth
            else if (cell.zoneType == 'I') {
                int adjacentPowerline = isAdjacentTo(cell, 'T', 0, i, j);
                int adjacentRes = isAdjacentTo(cell, 'R', 1, i, j);  // Check for adjacent residential zones

                if (cell.population == 0 && adjacentPowerline > 0 && availableWorkers >= 2) {
                    newPopulations[i][j].population = 1;
                    availableWorkers -= 2;
                    std::cout << "Industrial zone grew at (" << i << ", " << j << ") to population 1." << std::endl;
                } else if (cell.population == 1 && adjacentRes >= 1 && availableWorkers >= 2) {
                    newPopulations[i][j].population = 2;
                    availableWorkers -= 2;
                    std::cout << "Industrial zone grew at (" << i << ", " << j << ") to population 2." << std::endl;
                }

                // Spread pollution from industrial zones
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (dx == 0 && dy == 0) continue;
                        int ni = i + dx;
                        int nj = j + dy;
                        if (ni >= 0 && ni < grid.size() && nj >= 0 && nj < grid[0].size()) {
                            grid[ni][nj].pollution += std::max(0, cell.population - 1);
                        }
                    }
                }
            }
            // Commercial Growth
            else if (cell.zoneType == 'C') {
                int adjacentCom = isAdjacentTo(cell, 'C', 1, i, j);
                int adjacentPowerline = isAdjacentTo(cell, 'T', 0, i, j);
                
                if (cell.population == 0 && adjacentPowerline > 0 && availableWorkers >= 1 && availableGoods >= 1) {
                    newPopulations[i][j].population = 1;
                    availableWorkers -= 1;
                    availableGoods -= 1;
                } else if (cell.population == 1 && adjacentCom >= 2 && availableWorkers >= 1 && availableGoods >= 1) {
                    newPopulations[i][j].population = 2;
                    availableWorkers -= 1;
                    availableGoods -= 1;
                }
            }
        }
    }

    // Update the grid with the new population values
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            grid[i][j].population = newPopulations[i][j].population;
        }
    }
}



// Define isAdjacentTo to check neighboring cells
int Region::isAdjacentTo(const Cell& cell, char zoneType, int minPopulation, int x, int y) const {
    static const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};  // Row offsets
    static const int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};  // Column offsets
    int count = 0;  // Count the number of adjacent matching cells
    for (int i = 0; i < 8; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size()) {
            const Cell& neighbor = grid[newX][newY];
            if (neighbor.zoneType == zoneType && neighbor.population >= minPopulation) {
                count++;
            }
        }
    }
    return count;  // Return the number of matching adjacent cells
}



bool Region::readRegionFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << fileName << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<Cell> row;
        std::stringstream ss(line);
        std::string cellData;

        while (std::getline(ss, cellData, ',')) {
            Cell cell;
            cell.zoneType = cellData[0];
            cell.population = 0;  // Initial population is 0
            cell.pollution = 0;   // Initial pollution is 0
            row.push_back(cell);
        }
        grid.push_back(row);
    }

    file.close();
    return true;
}

void Region::printRegion() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.zoneType == 'R' || cell.zoneType == 'C') {
                if (cell.population == 0) {
                    std::cout << cell.zoneType << " ";  // Print zone type if population is 0
                } else {
                    std::cout << cell.population << " ";  // Print population if > 0
                }
            } else if (cell.zoneType == 'I') {
                if (cell.population == 0) {
                    std::cout << 'I' << " ";  // Print 'I' for industrial zones with no population
                } else {
                    // Add debug output for industrial zones
                    std::cout << cell.population << "(I) ";  // Print population for industrial zones
                    std::cout << "(Pop: " << cell.population << ") ";  // Debugging line
                }
            } else {
                std::cout << cell.zoneType << " ";  // For roads, powerlines, etc.
            }
        }
        std::cout << std::endl;  // New line after each row
    }
}





int Region::getTotalPopulation() const {
    int totalPopulation = 0;
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            totalPopulation += cell.population;
        }
    }
    return totalPopulation;
}

int Region::getAvailableWorkers() const {
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

int Region::getAvailableGoods() const {
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


void Region::printRegionWithPopulation() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.zoneType == 'R') {
                // Print residential zones with population in parentheses
                std::cout << "R(" << cell.population << ") ";
            } else if (cell.zoneType == 'I') {
                // Print industrial zones with population in parentheses
                std::cout << "I(" << cell.population << ") ";
            } else {
                // Print other zone types without population
                std::cout << cell.zoneType << " ";
            }
        }
        std::cout << std::endl;  // Newline after each row
    }
}
