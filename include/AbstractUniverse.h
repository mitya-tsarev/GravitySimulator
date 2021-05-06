#ifndef GRAVITYSIMULATOR_ABSTRACTUNIVERSE_H
#define GRAVITYSIMULATOR_ABSTRACTUNIVERSE_H

#include <vector>
#include "Body.h"

class AbstractUniverse {
protected:
    virtual const std::vector<Body *> &getBodies() const = 0;

public:
    std::vector<mathing::Vec4> getPosList();
    std::vector<mathing::Vec4> getVelList();
    virtual void addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) = 0;
};


#endif //GRAVITYSIMULATOR_ABSTRACTUNIVERSE_H
