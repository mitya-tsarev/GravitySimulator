#ifndef GRAVITYSIMULATOR_SIMULATOR_H
#define GRAVITYSIMULATOR_SIMULATOR_H

#include "BarnesHutUniverse.h"


class Simulator {
private:
    std::string initFile;
    AbstractUniverse *u;

    void addBody(double m, double x, double y, double z, double vx, double vy, double vz);

public:
    Simulator() = delete;

    explicit Simulator(std::ifstream & inputfile);
    std::vector<std::string> getwords (std::string sentence);
    void simulate();
};


#endif //GRAVITYSIMULATOR_SIMULATOR_H
