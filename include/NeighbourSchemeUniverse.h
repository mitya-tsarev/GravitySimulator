#ifndef GRAVITYSIMULATOR_NEIGHBOURSCHEMEUNIVERSE_H
#define GRAVITYSIMULATOR_NEIGHBOURSCHEMEUNIVERSE_H


#include "AbstractUniverse.h"
#include "HermitBody.h"

class NeighbourSchemeUniverse : public AbstractUniverse {
protected:
    std::vector<HermitBody *> body;
    double dt;
public:
    explicit NeighbourSchemeUniverse(double dt);

    void addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) override;
    std::vector<mathing::Vec4> getPosList() override;
    std::vector<mathing::Vec4> getVelList() override;
    void update(double time) override;
};


#endif //GRAVITYSIMULATOR_NEIGHBOURSCHEMEUNIVERSE_H
