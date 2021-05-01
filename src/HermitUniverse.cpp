#include "../include/HermitUniverse.h"

HermitUniverse::HermitUniverse(double dt) : dt(dt) {}

void HermitUniverse::addBody(mathing::Vec4 pos, mathing::Vec4 vel) {
    body.push_back(new HermitBody(pos, vel));
}

const std::vector<Body *> &HermitUniverse::getBodies() const {
    auto b_list = std::vector<Body *>();
    // for (auto b : body) b_list.push_back(dynamic_cast<Body*>(b));
    return b_list; //FIXME
}