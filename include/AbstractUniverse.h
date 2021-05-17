#ifndef GRAVITYSIMULATOR_ABSTRACTUNIVERSE_H
#define GRAVITYSIMULATOR_ABSTRACTUNIVERSE_H

#include <vector>
#include "Body.h"
#include <cmath>

class AbstractUniverse {

public:
    const double G = 4 * M_PI * M_PI;
    virtual std::vector<mathing::Vec4> getPosList() = 0;
    virtual std::vector<mathing::Vec4> getVelList() = 0;
    virtual std::vector<double> getMassList() = 0;
    virtual void setMomentum(mathing::Vec4 momentum) = 0;
    virtual void setBarycenter(mathing::Vec4 barycentre) = 0;
    virtual void addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) = 0;
    virtual void update(double time) = 0;
};


#endif //GRAVITYSIMULATOR_ABSTRACTUNIVERSE_H
