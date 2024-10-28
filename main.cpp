<<<<<<< HEAD
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

=======
#include "Simulation.h"
#include <iostream>
using namespace std;

int main() {
    string configFile;
    cout << "Enter the configuration file: ";
    cin >> configFile;

    // Read the configuration
    Config config = readConfig(configFile);

    // Pass the config to the Simulation
    Simulation sim(config);
    sim.run();
    
    int x1, y1, x2, y2;
    cout << "Enter coordinates for regional analysis (x1 y1 x2 y2): ";
    cin >> x1 >> y1 >> x2 >> y2;
    
    sim.analyzeRegion(x1, y1, x2, y2);
    
>>>>>>> origin/main
    return 0;
}
