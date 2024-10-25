#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config {
private:
    std::string regionFile;
    int maxTimeSteps;
    int refreshRate;

public:
    bool loadConfig(const std::string& fileName);
    std::string getRegionFile() const { return regionFile; }
    int getMaxTimeSteps() const { return maxTimeSteps; }
    int getRefreshRate() const { return refreshRate; }
};

#endif
