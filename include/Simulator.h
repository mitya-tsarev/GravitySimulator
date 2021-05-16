#ifndef GRAVITYSIMULATOR_SIMULATOR_H
#define GRAVITYSIMULATOR_SIMULATOR_H

#include <map>
#include "BarnesHutUniverse.h"
#include "../include/SimpleUniverse.h"



class Simulator {
private:
    std::string initFile;
    AbstractUniverse *u;
    double runtime;
    int nframes;
    std::vector<std::string> save_params;
    std::string perBodyOutputFilename;
public:
    Simulator() = delete;
    explicit Simulator(std::ifstream & inputfile);
    void simulate();
    void write_vtk(std::string filename);
    std::vector<double> getPerBodyVels();
};


#endif //GRAVITYSIMULATOR_SIMULATOR_H
