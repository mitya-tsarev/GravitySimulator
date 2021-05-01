#ifndef GRAVITYSIMULATOR_BHUNIVERSE_H
#define GRAVITYSIMULATOR_BHUNIVERSE_H

#include "AbstractUniverse.h"

class BHUniverse : public AbstractUniverse {
protected:
    std::vector<Body *> body;
    double dt;
public:
    explicit BHUniverse(double dt);

    const std::vector<Body *> &getBodies() const override;

    void addBody(mathing::Vec4 pos, mathing::Vec4 vel) override;
};


#endif //GRAVITYSIMULATOR_BHUNIVERSE_H
