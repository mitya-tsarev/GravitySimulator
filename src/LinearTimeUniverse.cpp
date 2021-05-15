#include "../include/LinearTimeUniverse.h"

LinearTimeUniverse::LinearTimeUniverse(double dt) : dt(dt) {}

void LinearTimeUniverse::addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) {
    body.push_back(new Body(pos, vel, mass));
}

void LinearTimeUniverse::update(double time) {
    for (double t_final = global_time + time; global_time < t_final; global_time += dt) updateAccels();
}

std::vector<mathing::Vec4> LinearTimeUniverse::getVelList() {
    std::vector<mathing::Vec4> VelList;
    for(auto b : body) VelList.push_back(b->getVel());
    return VelList;
}

std::vector<mathing::Vec4> LinearTimeUniverse::getPosList() {
    std::vector<mathing::Vec4> PosList;
    for(auto b : body) PosList.push_back(b->getPos());
    return PosList;
}

void LinearTimeUniverse::setDt(double dt) {
    LinearTimeUniverse::dt = dt;
}
