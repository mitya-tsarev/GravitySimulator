#ifndef GRAVITYSIMULATOR_BARNESHUTUNIVERSE_H
#define GRAVITYSIMULATOR_BARNESHUTUNIVERSE_H

#include "LinearTimeUniverse.h"
#include "OctTree.h"

class BarnesHutUniverse : public LinearTimeUniverse {
    double TAU;
    OctTree* tree = nullptr;
public:
    BarnesHutUniverse() = delete;
    explicit BarnesHutUniverse(double dt, double tau, int method);
    void updateAccels() override;
    void constructTree(double smoothParam=0);
    void destroyTree();
};


#endif //GRAVITYSIMULATOR_BARNESHUTUNIVERSE_H
