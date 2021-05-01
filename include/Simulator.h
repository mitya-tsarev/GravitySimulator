#ifndef GRAVITYSIMULATOR_SIMULATOR_H
#define GRAVITYSIMULATOR_SIMULATOR_H

#include "BHUniverse.h"


class Simulator {
private:
    std::string initFile;
    AbstractUniverse *u;

    void addBodies();

public:
    Simulator() = delete;

    explicit Simulator(std::string initFile);
    void simulate(const std::string& outFile, double time);
};


#endif //GRAVITYSIMULATOR_SIMULATOR_H
