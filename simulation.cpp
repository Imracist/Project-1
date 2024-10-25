#include "simulation.h"
#include <iostream>
#include <string>

Simulation::Simulation(const Config& config, const Region& region)
    : config(config), region(region), currentTimeStep(0) {}

void Simulation::run() {
    int maxTimeSteps = config.getMaxTimeSteps();
    int previousPopulation = -1;

    while (currentTimeStep < maxTimeSteps) {
        currentTimeStep++;  // Increment the stage number

        // Simulate one step of growth
        region.simulateGrowth();

        // Output the region state for the current stage
        std::cout << "===================\n";
        std::cout << "Stage: " << currentTimeStep << "\n";
        std::cout << "===================\n";
        region.printRegionWithPopulation();  // Print the region layout with population
        std::cout << "\nPress Enter to proceed to the next stage or 'q' to quit: ";
        
        // Check for population change
        int currentPopulation = region.getTotalPopulation();
        if (currentPopulation == previousPopulation) {
            std::cout << "\nNo change in population. Stopping simulation at time step " << currentTimeStep << "." << std::endl;
            break;
        }

        // Prompt user to proceed or quit
        std::string input;
        std::getline(std::cin, input);
        if (input == "q" || input == "Q") {
            std::cout << "Simulation stopped by user at time step " << currentTimeStep << "." << std::endl;
            break;
        }

        previousPopulation = currentPopulation;
    }

    // Final state output
    std::cout << "===================\n";
    std::cout << "Final Stage: " << currentTimeStep << "\n";
    std::cout << "===================\n";
    region.printRegionWithPopulation();  // Final region print
    std::cout << "==========\n";  // Final separator line
}
