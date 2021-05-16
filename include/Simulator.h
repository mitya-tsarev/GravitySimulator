#ifndef GRAVITYSIMULATOR_SIMULATOR_H
#define GRAVITYSIMULATOR_SIMULATOR_H

#include "BarnesHutUniverse.h"
#include "../include/SimpleUniverse.h"



class Simulator {
private:
    std::string initFile;
    AbstractUniverse *u;
    double runtime;
    int nframes;
public:
    Simulator() = delete;

    explicit Simulator(std::ifstream & inputfile);
    void simulate();
    void write_vtk(std::string filename);
};


#endif //GRAVITYSIMULATOR_SIMULATOR_H
