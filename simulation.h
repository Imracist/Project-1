#ifndef SIMULATION_H
#define SIMULATION_H

#include "config.h"
#include "region.h"

class Simulation {
private:
    Config config;
    Region region;
    int currentTimeStep;

public:
    Simulation(const Config& config, const Region& region);
    void run();

private:
    // Declare the printWorkersAndGoods function here
    void printWorkersAndGoods() const;
};


#endif
