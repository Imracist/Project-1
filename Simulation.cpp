#include "Simulation.h"
#include <fstream>

Simulation::Simulation(const Config& config)
    : pollution(8, 8), timeLimit(config.timeLimit), refreshRate(config.refreshRate), workers(0), goods(0) {
    // Load region from file
    std::ifstream file(config.regionFile);
    std::string line;
    while (getline(file, line)) {
        std::vector<char> row;
        for (char c : line) {
            if (c != ',') {
                row.push_back(c);
            }
        }
        region.push_back(row);
    }
    population = std::vector<std::vector<int>>(region.size(), std::vector<int>(region[0].size(), 0));
}

void Simulation::run() {
    int timeStep = 0;
    bool stable = false;
    
    while (timeStep < timeLimit && !stable) {
        std::cout << "Time Step: " << timeStep << std::endl;
        displayRegion();
        simulateStep();
        timeStep++;
        if (timeStep % refreshRate == 0) {
            displayRegion();
        }
        stable = checkForStability();
    }
}

void Simulation::simulateStep() {
    // Iterate through the grid and grow each zone
    for (int i = 0; i < region.size(); i++) {
        for (int j = 0; j < region[i].size(); j++) {
            if (region[i][j] == 'R') {
                Zone residential(Residential);
                residential.grow(region, population, i, j);
                workers++;
            } else if (region[i][j] == 'I') {
                Zone industrial(Industrial);
                industrial.grow(region, population, i, j);
                pollution.spreadPollution(i, j, population[i][j]);
                goods++;
            } else if (region[i][j] == 'C') {
                Zone commercial(Commercial);
                commercial.grow(region, population, i, j);
            }
        }
    }
}

bool Simulation::checkForStability() const {
    // Logic to check if the grid is stable
    return false; // Placeholder, you'll add more sophisticated logic here.
}

void Simulation::displayRegion() const {
    for (int i = 0; i < region.size(); i++) {
        for (int j = 0; j < region[i].size(); j++) {
            if (population[i][j] > 0) {
                std::cout << population[i][j] << " ";
            } else {
                std::cout << region[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Simulation::analyzeRegion(int x1, int y1, int x2, int y2) const {
    int residentialPop = 0, industrialPop = 0, commercialPop = 0, totalPollution = 0;

    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            if (region[i][j] == 'R') {
                residentialPop += population[i][j];
            } else if (region[i][j] == 'I') {
                industrialPop += population[i][j];
            } else if (region[i][j] == 'C') {
                commercialPop += population[i][j];
            }
            totalPollution += pollution.pollutionMap[i][j];
        }
    }

    std::cout << "Residential Population: " << residentialPop << std::endl;
    std::cout << "Industrial Population: " << industrialPop << std::endl;
    std::cout << "Commercial Population: " << commercialPop << std::endl;
    std::cout << "Total Pollution: " << totalPollution << std::endl;
}
