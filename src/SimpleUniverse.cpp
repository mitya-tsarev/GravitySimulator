#include "../include/SimpleUniverse.h"

SimpleUniverse::SimpleUniverse(double dt, int method) : LinearTimeUniverse(dt, method) {}

void SimpleUniverse::updateAccels() {
    for(auto b : body){
        b->setAccel(mathing::Vec4());
    }

    for(auto b_ : body){
        if(b_->getMass() > 1e-12){
            for(auto b : body){
                mathing::Vec4 dr = b->getPos() - b_->getPos();
                if(dr.Length3() > 1e-4){
                    b->setAccel(b->getAccel() - G * b_->getMass() * dr/(dr.Length3()*dr.Length3Sqr()));
                }else{
                    b->setAccel(b->getAccel() - G * b_->getMass() * dr * 1e12);
                }
            }
        }
    }
}