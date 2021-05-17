#include "../include/BarnesHutUniverse.h"

BarnesHutUniverse::BarnesHutUniverse(double dt, double tau, int method) : LinearTimeUniverse(dt, method), TAU(tau) {}

void BarnesHutUniverse::updateAccels() {
    constructTree();
    for (auto b : body) {
        b->setAccel(tree->get_accel(b->getPos()));
    }
}

void BarnesHutUniverse::constructTree(double smoothParam) {
    tree = new OctTree(minCoord, maxCoord, smoothParam);
    tree->insert(body);
}

void BarnesHutUniverse::destroyTree() {
    delete tree;
}

