#include "Config.h"
#include <iostream>
#include <fstream>

Config readConfig(const std::string& filename) {
    Config config;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config file." << std::endl;
        exit(1);
    }

    std::string line;
    while (getline(file, line)) {
        if (line.find("Region Layout:") != std::string::npos) {
            config.regionFile = line.substr(line.find(":") + 1);
        } else if (line.find("Time Limit:") != std::string::npos) {
            config.timeLimit = std::stoi(line.substr(line.find(":") + 1));
        } else if (line.find("Refresh Rate:") != std::string::npos) {
            config.refreshRate = std::stoi(line.substr(line.find(":") + 1));
        }
    }

    file.close();
    return config;
}
