#ifndef SIMULATION_H
#define SIMULATION_H

#include "config.h"
#include "region.h"

class Simulation {
public:
    Simulation(const Config& config, Region& region);
    void run();

private:
    const Config& config;
    Region& region;
};

#endif
