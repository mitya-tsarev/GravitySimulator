#include "../include/LinearTimeUniverse.h"

LinearTimeUniverse::LinearTimeUniverse(double dt) : dt(dt) {}

void LinearTimeUniverse::addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) {
    body.push_back(new Body(pos, vel, mass));
}

void LinearTimeUniverse::update(double time) {

}

std::vector<mathing::Vec4> LinearTimeUniverse::getVelList() {
    return std::vector<mathing::Vec4>();
}

std::vector<mathing::Vec4> LinearTimeUniverse::getPosList() {
    return std::vector<mathing::Vec4>();
}
