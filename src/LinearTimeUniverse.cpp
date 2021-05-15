#include "../include/LinearTimeUniverse.h"

LinearTimeUniverse::LinearTimeUniverse(double dt) : dt(dt) {}

void LinearTimeUniverse::addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) {
    body.push_back(new Body(pos, vel, mass));
}

void LinearTimeUniverse::Step() {
    updateAccels();
    for(auto b : body){
        b->setPos(b->getPos()+dt*b->getVel() + dt*dt*b->getAccel()/2);
        b->setVel(b->getVel()+dt*b->getAccel());
    }
}

void LinearTimeUniverse::update(double time) {
    int32_t steps = global_time / time;
    for (int32_t i = 0; i < steps; i++) Step();
    global_time += time;
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
