#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config {
public:
    bool readConfigFile(const std::string &fileName);
    std::string getRegionLayoutFile() const { return regionLayoutFile; }
    int getMaxTimeSteps() const { return maxTimeSteps; }
    int getRefreshRate() const { return refreshRate; }

private:
    std::string regionLayoutFile;
    int maxTimeSteps;
    int refreshRate;
};

#endif
