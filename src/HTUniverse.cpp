#include "../include/HTUniverse.h"

HTUniverse::HTUniverse(double dt) : dt(dt) {}

void HTUniverse::addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) {
    body.push_back(new Body(pos, vel, mass));
}