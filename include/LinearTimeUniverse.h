#ifndef GRAVITYSIMULATOR_LINEARTIMEUNIVERSE_H
#define GRAVITYSIMULATOR_LINEARTIMEUNIVERSE_H


#include "AbstractUniverse.h"

class LinearTimeUniverse : public AbstractUniverse {
protected:
    std::vector<Body *> body;
    double dt;
    double global_time = 0;
public:
    explicit LinearTimeUniverse(double dt, int method);
    virtual ~LinearTimeUniverse();

    int method = 0; //0 - Euler, 1 - Runge-Kutta

    void Step();
    //void AdvancedEulerStep();
    void RungeKuttaStep();
    void EulerStep();

    void addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) override;
    void update(double time) override;
    std::vector<mathing::Vec4> getPosList() override;
    std::vector<mathing::Vec4> getVelList() override;
    std::vector<double> getMassList() override;
    void setBarycenter(mathing::Vec4 barycenter) override;
    void setMomentum(mathing::Vec4 momentum) override;
    virtual void updateAccels() = 0;
};


#endif //GRAVITYSIMULATOR_LINEARTIMEUNIVERSE_H
