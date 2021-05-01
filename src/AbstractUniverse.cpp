#include "../include/AbstractUniverse.h"

std::vector<mathing::Vec4> AbstractUniverse::getPosList() {
    auto positions = std::vector<mathing::Vec4>();
    for (auto b : getBodies()) positions.push_back(b->getPos());
    return positions;
}

std::vector<mathing::Vec4> AbstractUniverse::getVelList() {
    auto velocities = std::vector<mathing::Vec4>();
    for (auto b : getBodies()) velocities.push_back(b->getVel());
    return velocities;
}
