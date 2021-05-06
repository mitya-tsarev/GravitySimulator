#ifndef GRAVITYSIMULATOR_HERMITBODY_H
#define GRAVITYSIMULATOR_HERMITBODY_H

#include "Body.h"

class HermitBody : public Body {
protected:
    mathing::Vec4 accel;
    mathing::Vec4 jerk;
public:
    HermitBody(const mathing::Vec4 &pos, const mathing::Vec4 &vel, const mathing::Vec4 &accel,
                const mathing::Vec4 &jerk, double mass);

    HermitBody(const mathing::Vec4 &pos, const mathing::Vec4 &vel);

    HermitBody();
};


#endif //GRAVITYSIMULATOR_HERMITBODY_H
