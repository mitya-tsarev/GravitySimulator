#ifndef GRAVITYSIMULATOR_SIMULATOR_H
#define GRAVITYSIMULATOR_SIMULATOR_H

#include <map>
#include "../include/BarnesHutUniverse.h"
#include "../include/SimpleUniverse.h"
#include "../include/utilities.h"



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

    virtual ~Simulator();

    void simulate();
    void write_vtk(const std::string& filename);
    std::vector<double> getPerBodyVels();
    double getPotEng();
    double getKinEng();
    mathing::Vec4 getMomentum();
    mathing::Vec4 getBarycenter();
    void addCluster(std::vector<std::string> words);
};


#endif //GRAVITYSIMULATOR_SIMULATOR_H
