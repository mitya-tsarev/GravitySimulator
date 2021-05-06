#include "../include/HTUniverse.h"

HTUniverse::HTUniverse(double dt) : dt(dt) {}

void HTUniverse::addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) {
    body.push_back(new Body(pos, vel, mass));
}

void HTUniverse::update(double time) {

}

std::vector<mathing::Vec4> HTUniverse::getVelList() {
    return std::vector<mathing::Vec4>();
}

std::vector<mathing::Vec4> HTUniverse::getPosList() {
    return std::vector<mathing::Vec4>();
}
