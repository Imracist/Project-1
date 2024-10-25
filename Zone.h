#ifndef ZONE_H
#define ZONE_H

#include <vector>
#include <iostream>

enum ZoneType { Residential, Industrial, Commercial };

class Zone {
public:
    ZoneType type;
    int population;
    Zone(ZoneType type);
    void grow(const std::vector<std::vector<char>>& region, std::vector<std::vector<int>>& population, int x, int y);
};

#endif
