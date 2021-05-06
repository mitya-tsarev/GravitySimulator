#include "../include/Simulator.h"

#include <utility>

Simulator::Simulator(std::string initFile) : initFile(std::move(initFile)) {
    u = new BHUniverse(1);
    addBodies();
}

void Simulator::addBodies() {
    u->addBody(mathing::Vec4(179,3,1,0), mathing::Vec4(), 1);
}

void Simulator::simulate(const std::string& outFile, double time) {
    auto list = u->getPosList();
    std::cout << "x position of first body is " << list[0].x << std::endl;
}
