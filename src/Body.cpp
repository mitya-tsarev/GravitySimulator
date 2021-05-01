#include "../include/Body.h"

Body::Body(const mathing::Vec4 &pos, const mathing::Vec4 &vel) : pos(pos), vel(vel) {}

Body::Body() : Body(mathing::Vec4(), mathing::Vec4()) {}

const mathing::Vec4 &Body::getPos() const {
    return pos;
}

const mathing::Vec4 &Body::getVel() const {
    return vel;
}
