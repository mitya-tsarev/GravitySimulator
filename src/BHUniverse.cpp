#include "../include/BHUniverse.h"

BHUniverse::BHUniverse(double dt) : dt(dt) {}

void BHUniverse::addBody(mathing::Vec4 pos, mathing::Vec4 vel) {
    body.push_back(new Body(pos, vel));
}

const std::vector<Body *> &BHUniverse::getBodies() const {
    return body;
}
