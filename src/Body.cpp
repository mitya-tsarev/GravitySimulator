#include "../include/Body.h"

Body::Body(const mathing::Vec4 &pos, const mathing::Vec4 &vel, double mass) : pos(pos), vel(vel), mass(mass),
                                                                              accel(mathing::Vec4()) {}

Body::Body() : Body(mathing::Vec4(), mathing::Vec4(), 0) {}

const mathing::Vec4 &Body::getPos() const {
    return pos;
}

const mathing::Vec4 &Body::getVel() const {
    return vel;
}

const mathing::Vec4 &Body::getAccel() const {
    return accel;
}
