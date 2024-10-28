#include "config.h"
#include <fstream>
#include <iostream>

bool Config::readConfigFile(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) return false;

    std::getline(file, regionLayoutFile);
    file >> maxTimeSteps >> refreshRate;

    return true;
}
