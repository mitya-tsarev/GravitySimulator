#ifndef GRAVITYSIMULATOR_BARNESHUTUNIVERSE_H
#define GRAVITYSIMULATOR_BARNESHUTUNIVERSE_H

#include "LinearTimeUniverse.h"
#include "OctTree.h"

class BarnesHutUniverse : public LinearTimeUniverse {
    double TAU;
    OctTree* tree;
public:
    explicit BarnesHutUniverse(double dt, double tau, int method);

    void updateAccels() override;
};


#endif //GRAVITYSIMULATOR_BARNESHUTUNIVERSE_H
