#include "../include/SimpleUniverse.h"

SimpleUniverse::SimpleUniverse(double dt, int method) : LinearTimeUniverse(dt) {}

void SimpleUniverse::updateAccels() {
    for(auto b : body){
        mathing::Vec4 r = b->getPos();
        mathing::Vec4 accel;
        for(auto b_ : body){
            double dist = (r - b_->getPos()).Length3();
            mathing::Vec4 a_;
            if (dist > 1e-8) a_ = - G * b_->getMass()*(r - b_->getPos())/(dist*dist*dist);
            accel += a_;
        }
        b->setAccel(accel);
    }
}