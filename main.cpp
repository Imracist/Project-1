#include <iostream>
#include "config.h"
#include "region.h"
#include "simulation.h"

int main() {
    std::string configFileName;
    std::cout << "Enter the config file name: ";
    std::cin >> configFileName;

    Config config;
    if (!config.readConfigFile(configFileName)) {
        std::cerr << "Failed to read configuration file." << std::endl;
        return 1;
    }

    Region region;
    // Change this line to use getRegionLayoutFile() instead of getRegionLayout()
    if (!region.readRegionFile(config.getRegionLayoutFile())) {
        std::cerr << "Failed to read region layout file." << std::endl;
        return 1;
    }

    Simulation simulation(config, region);
    simulation.run();

    return 0;
}
