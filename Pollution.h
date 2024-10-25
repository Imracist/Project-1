#ifndef POLLUTION_H
#define POLLUTION_H

#include <vector>
using namespace std;

class Pollution {
public:
    std::vector<std::vector<int>> pollutionMap;
    Pollution(int width, int height);
    void spreadPollution(int x, int y, int population);
    void displayPollution() const;
};

#endif
