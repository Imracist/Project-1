#ifndef CONFIG_H
#define CONFIG_H

#include <string>

struct Config {
    std::string regionFile;
    int timeLimit;
    int refreshRate;
};

Config readConfig(const std::string& filename);

#endif
