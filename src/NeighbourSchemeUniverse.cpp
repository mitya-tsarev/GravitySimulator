#include "../include/NeighbourSchemeUniverse.h"

NeighbourSchemeUniverse::NeighbourSchemeUniverse(double dt) : dt(dt) {}

void NeighbourSchemeUniverse::addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) {
    body.push_back(new HermitBody(pos, vel, mass));
}

void NeighbourSchemeUniverse::update(double time) {

}

std::vector<mathing::Vec4> NeighbourSchemeUniverse::getVelList() {
    return std::vector<mathing::Vec4>();
}

std::vector<mathing::Vec4> NeighbourSchemeUniverse::getPosList() {
    return std::vector<mathing::Vec4>();
}
