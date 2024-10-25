#include "config.h"
#include <fstream>
#include <iostream>
#include <sstream>

bool Config::loadConfig(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening config file: " << fileName << std::endl;
        return false;
    }

    std::string line;

    // Read the first line which contains "Region Layout:region1.csv"
    std::getline(file, line);

    // Find and extract the region file name
    std::string keyword = "Region Layout:";
    size_t pos = line.find(keyword);
    if (pos == std::string::npos) {
        std::cerr << "Error: 'Region Layout:' not found in config file." << std::endl;
        return false;
    }

    // Extract the region file name
    regionFile = line.substr(pos + keyword.length());
    regionFile.erase(0, regionFile.find_first_not_of(" \t"));  // Trim leading spaces

    // Read the time limit (second line)
    if (!(file >> maxTimeSteps)) {
        std::cerr << "Error reading time limit from config file." << std::endl;
        return false;
    }

    // Read the refresh rate (third line)
    if (!(file >> refreshRate)) {
        std::cerr << "Error reading refresh rate from config file." << std::endl;
        return false;
    }

    file.close();
    return true;
}
