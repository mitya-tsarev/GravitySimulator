#ifndef GRAVITYSIMULATOR_BODY_H
#define GRAVITYSIMULATOR_BODY_H

#include "vector.h"

class Body {
protected:
    mathing::Vec4 pos;
    mathing::Vec4 vel;
    mathing::Vec4 accel;
    double mass;
public:
    Body();
    Body(const mathing::Vec4 &pos, const mathing::Vec4 &vel, const mathing::Vec4 &accel, double mass);
    Body(const mathing::Vec4 &pos, const mathing::Vec4 &vel, double mass);

    const mathing::Vec4 &getPos() const;

    const mathing::Vec4 &getVel() const;

    const mathing::Vec4 &getAccel() const;

    void setAccel(const mathing::Vec4 &accel);

    double getMass() const;

    void setPos(const mathing::Vec4 &pos);

    void setVel(const mathing::Vec4 &vel);
};


#endif //GRAVITYSIMULATOR_BODY_H
