#include "simulation.h"
#include <iostream>

Simulation::Simulation(const Config& config, Region& region)
    : config(config), region(region) {}

void Simulation::run() {
    int maxTimeSteps = config.getMaxTimeSteps();
    int refreshRate = config.getRefreshRate();
    region.printRegion(0);  // Print initial state

    for (int step = 1; step <= maxTimeSteps; ++step) {
        region.simulateGrowth(step, refreshRate);
        std::cout << "Available Workers: " << region.calculateAvailableWorkers() << std::endl;
        std::cout << "Available Goods: " << region.calculateAvailableGoods() << std::endl;
    }
}
