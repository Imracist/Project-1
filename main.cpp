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
    
    return 0;
}
