#include "../include/SimpleUniverse.h"

SimpleUniverse::SimpleUniverse(double dt, int method) : LinearTimeUniverse(dt) {}

void SimpleUniverse::updateAccels() {
    for(auto b : body){
        mathing::Vec4 r = b->getPos();
        mathing::Vec4 accel;
        for(auto b_ : body){
            mathing::Vec4 r_ = b_->getPos();
            double dist = (r - r_).Length3();
            mathing::Vec4 a_;
            if (dist > 1e-8) a_ = 39.478417604357434475*b->getMass()*b_->getMass()*(r - r_)/(dist*dist*dist);
            accel += a_;
        }
        b->setAccel(accel);
    }
}