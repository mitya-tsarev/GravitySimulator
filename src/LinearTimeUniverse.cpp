#include "../include/LinearTimeUniverse.h"

LinearTimeUniverse::LinearTimeUniverse(double dt, int method) : dt(dt), method(method) {}

void LinearTimeUniverse::addBody(mathing::Vec4 pos, mathing::Vec4 vel, double mass) {
    body.push_back(new Body(pos, vel, mass));
}

void LinearTimeUniverse::Step() {
    if (method == 0)EulerStep();
    else if (method == 1)RungeKuttaStep();
}

void LinearTimeUniverse::EulerStep() {
    updateAccels();
    for(auto b : body){
        b->setPos(b->getPos()+dt*b->getVel() + dt*dt*b->getAccel()/2);
        b->setVel(b->getVel()+dt*b->getAccel());
    }
}

/* Now it is useless.
void LinearTimeUniverse::AdvancedEulerStep() {
    updateAccels();
    std::vector<Body *> old_body = std::move(body);
    body.clear();
    for(auto b : old_body){
        body.push_back(new Body(b->getPos()+dt*b->getVel(),
                                b->getVel()+dt*b->getAccel(),
                                b->getMass()));
    }
    updateAccels();

    for(int i = 0;i < body.size();i++){
        auto b = body[i];
        auto b_old = old_body[i];
        body[i]->setVel(b_old->getVel() + dt/2*(b_old->getAccel() + b->getAccel()));
        body[i]->setPos(b_old->getPos() + dt/2*(b_old->getVel() + b->getVel()));
    }
} */

void LinearTimeUniverse::RungeKuttaStep() {
    updateAccels();
    std::vector<Body *> k1 = std::move(body);
    for(auto b : k1){
        body.push_back(new Body(b->getPos()+dt/2*b->getVel(),
                                b->getVel()+dt/2*b->getAccel(),
                                b->getMass()));
    }
    updateAccels();
    std::vector<Body *> k2 = std::move(body);
    for(int i = 0;i < k1.size();i++){
        auto b = k1[i];
        auto b2 = k2[i];
        body.push_back(new Body(b->getPos()+dt/2*b2->getVel(),
                                b->getVel()+dt/2*b2->getAccel(),
                                b->getMass()));
    }
    updateAccels();
    std::vector<Body *> k3 = std::move(body);
    for(int i = 0;i < k1.size();i++){
        auto b = k1[i];
        auto b3 = k3[i];
        body.push_back(new Body(b->getPos()+dt*b3->getVel(),
                                b->getVel()+dt*b3->getAccel(),
                                b->getMass()));
    }
    updateAccels();
    std::vector<Body *> k4 = std::move(body);
    for(int i = 0;i < k1.size();i++){
        auto b1 = k1[i];
        auto b2 = k2[i];
        auto b3 = k3[i];
        auto b4 = k4[i];
        body.push_back(new Body(b1->getPos()+dt/6*(b1->getVel()+2*b2->getVel()+2*b3->getVel()+b4->getVel()),
                                b1->getVel()+dt/6*(b1->getAccel()+2*b2->getAccel()+2*b3->getAccel()+b4->getAccel()),
                                b1->getMass()));
    }
}

void LinearTimeUniverse::update(double time) {
    auto steps = (uint32_t) (time / dt);
    for (uint32_t i = 0; i < steps; i++) Step();
    global_time += time;
}

std::vector<mathing::Vec4> LinearTimeUniverse::getVelList() {
    std::vector<mathing::Vec4> VelList;
    for(auto b : body) VelList.push_back(b->getVel());
    return VelList;
}

std::vector<mathing::Vec4> LinearTimeUniverse::getPosList() {
    std::vector<mathing::Vec4> PosList;
    for(auto b : body) PosList.push_back(b->getPos());
    return PosList;
}

std::vector<double> LinearTimeUniverse::getMassList() {
    std::vector<double> MassList;
    for(auto b : body) MassList.push_back(b->getMass());
    return MassList;
}

void LinearTimeUniverse::setBarycenter(mathing::Vec4 barycenter) {
    double sumMass = 0;
    mathing::Vec4 sumPos = mathing::Vec4();
    for (auto b : body) {
        sumPos += b->getPos() * b->getMass();
        sumMass += b->getMass();
    }
    mathing::Vec4 shift = barycenter - (sumPos / sumMass);
    for (auto b : body) {
        b -> setPos(b->getPos() + shift);
    }
}

void LinearTimeUniverse::setMomentum(mathing::Vec4 momentum) {
    double sumMass = 0;
    mathing::Vec4 sumVel = mathing::Vec4();
    for (auto b : body) {
        sumVel += b->getPos() * b->getMass();
        sumMass += b->getMass();
    }
    mathing::Vec4 velShift = momentum - (sumVel / sumMass);
    for (auto b : body) {
        b -> setVel(b->getVel() + velShift);
    }
}
