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
    std::vector<std::string> savePerBody;
    std::vector<std::string> saveGlobal;
    std::string perBodyOutputFilename;
    std::string globalOutputFilename;
public:
    Simulator() = delete;
    explicit Simulator(std::ifstream & inputfile);
    void simulate();
    void write_vtk(const std::string& filename);
    std::vector<double> getPerBodyVels();
    double getPotEng();
    double getKinEng();
    mathing::Vec4 getMomentum();
    mathing::Vec4 getBarycenter();
};


#endif //GRAVITYSIMULATOR_SIMULATOR_H
