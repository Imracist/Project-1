#ifndef SIMULATION_H
#define SIMULATION_H

#include "Zone.h"
#include "Pollution.h"
#include "Config.h"

class Simulation {
public:
    Simulation(const Config& config);
    void run();
    void displayRegion() const;
    void analyzeRegion(int x1, int y1, int x2, int y2) const;
    
private:
    std::vector<std::vector<char>> region;
    std::vector<std::vector<int>> population;
    Pollution pollution;
    int timeLimit;
    int refreshRate;
    int workers, goods;
    void simulateStep();
    bool checkForStability() const;
};

#endif
