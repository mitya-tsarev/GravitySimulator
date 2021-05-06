#ifndef GRAVITYSIMULATOR_LINEARTIMEUNIVERSE_H
#define GRAVITYSIMULATOR_LINEARTIMEUNIVERSE_H


#include "AbstractUniverse.h"

class LinearTimeUniverse : public AbstractUniverse {
    std::vector<Body *> body;
    double dt;
public:
    explicit LinearTimeUniverse(double dt);

    void addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) override;
    std::vector<mathing::Vec4> getPosList() override;
    std::vector<mathing::Vec4> getVelList() override;
    void update(double time) override;

    virtual void updateAccels() = 0;
};


#endif //GRAVITYSIMULATOR_LINEARTIMEUNIVERSE_H