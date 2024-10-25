#include "Zone.h"

Zone::Zone(ZoneType type) : type(type), population(0) {}

void Zone::grow(const std::vector<std::vector<char>>& region, std::vector<std::vector<int>>& population, int x, int y) {
    // Simple logic to increase population based on type and neighboring cells
    if (type == Residential && population[x][y] < 5) {
        population[x][y]++;
    } else if (type == Industrial && population[x][y] < 3) {
        population[x][y]++;
    } else if (type == Commercial && population[x][y] < 3) {
        population[x][y]++;
    }
}
