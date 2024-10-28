#ifndef REGION_H
#define REGION_H

#include <vector>
#include <string>
#include <iostream>

class Region {
public:
    struct Cell {
        char zoneType = '-';   // Zone type (R, I, C, -, T, #, P)
        int population = 0;    // Population of the zone
        int pollution = 0;     // Pollution level
    };

private:
    std::vector<std::vector<Cell>> grid;

public:
    Region() = default;
    ~Region() = default;

    bool readRegionFile(const std::string &fileName);
    void printRegion(int step) const;
    void simulateGrowth(int maxSteps, int refreshRate);
    void analyzeArea(int x1, int y1, int x2, int y2) const;
    void outputFinalTotals() const;

    int calculateAvailableWorkers() const;
    int calculateAvailableGoods() const;

    int getTotalPopulation(char zoneType) const;
    int getTotalPollution() const;

private:
    int isAdjacentTo(const Cell& cell, char zoneType, int minPopulation, int x, int y) const;
};

#endif
