#include "../include/HermitUniverse.h"

HermitUniverse::HermitUniverse(double dt) : dt(dt) {}

void HermitUniverse::addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) {
    body.push_back(new HermitBody(pos, vel, mass));
}

void HermitUniverse::update(double time) {

}

std::vector<mathing::Vec4> HermitUniverse::getVelList() {
    return std::vector<mathing::Vec4>();
}

std::vector<mathing::Vec4> HermitUniverse::getPosList() {
    return std::vector<mathing::Vec4>();
}
