#include "../include/BarnesHutUniverse.h"

BarnesHutUniverse::BarnesHutUniverse(double dt, double tau, int method) : LinearTimeUniverse(dt, method), TAU(tau) {}

void BarnesHutUniverse::updateAccels() {
    constructTree();
    for (auto b : body) {
        b->setAccel(tree->get_accel(b->getPos()));
    }
}

void BarnesHutUniverse::constructTree(double smoothParam) {
    tree = new OctTree(getMinCoord(), getMaxCoord(), smoothParam);
    tree->insert(body);
}

void BarnesHutUniverse::destroyTree() {
    delete tree;
}

double BarnesHutUniverse::getMaxCoord() {
    double maxCoord = 0;
    double m = 0;
    for (auto b : body) {
        const auto& pos = b->getPos();
        m = std::max(std::max(pos.x, pos.y), pos.z);
        if (m > maxCoord) maxCoord = m;
    }
    return maxCoord;
}

double BarnesHutUniverse::getMinCoord() {
    double minCoord = 0;
    double m = 0;
    for (auto b : body) {
        const auto& pos = b->getPos();
        m = std::min(std::min(pos.x, pos.y), pos.z);
        if (m < minCoord) minCoord = m;
    }
    return minCoord;
}

