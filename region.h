#ifndef REGION_H
#define REGION_H

#include <vector>
#include <string>

struct Cell {
    char zoneType;   // R, I, C, -, T, #, P
    int population;  // Population of the zone
    int pollution;   // Pollution level
};

class Region {
private:
    std::vector<std::vector<Cell>> grid;

public:
    bool readRegionFile(const std::string& fileName);
    void printRegion() const;
    void simulateGrowth();
    int getAvailableWorkers() const;
    int getAvailableGoods() const;

    int getTotalPopulation() const;  // Declaration for total population function
    int getTotalPollution() const;   // Declaration for total pollution function

    void printRegionWithPopulation() const;

    // Declare the isAdjacentTo function here
    int isAdjacentTo(const Cell& cell, char zoneType, int minPopulation, int x, int y) const;

};

#endif
