#include <iostream>
#include "config.h"
#include "region.h"
#include "simulation.h"

int main() {
    Config config;
    if (!config.loadConfig("config1.txt")) {
        std::cerr << "Error reading config file!" << std::endl;
        return 1;
    }

    std::string regionFile = config.getRegionFile();
    std::cout << "Trying to load region layout from: " << regionFile << std::endl;

    Region region;
    if (!region.readRegionFile(regionFile)) {
        std::cerr << "Error reading region layout!" << std::endl;
        return 1;
    }

    Simulation simulation(config, region);
    simulation.run();

    return 0;
}
