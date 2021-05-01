#ifndef GRAVITYSIMULATOR_HERMITUNIVERSE_H
#define GRAVITYSIMULATOR_HERMITUNIVERSE_H


#include "AbstractUniverse.h"
#include "HermitBody.h"

class HermitUniverse : public AbstractUniverse {
protected:
    std::vector<HermitBody *> body;
    double dt;
public:
    explicit HermitUniverse(double dt);

    const std::vector<Body *> &getBodies() const override;

    void addBody(mathing::Vec4 pos, mathing::Vec4 vel) override;
};


#endif //GRAVITYSIMULATOR_HERMITUNIVERSE_H
