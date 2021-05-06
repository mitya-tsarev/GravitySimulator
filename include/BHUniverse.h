#ifndef GRAVITYSIMULATOR_BHUNIVERSE_H
#define GRAVITYSIMULATOR_BHUNIVERSE_H

#include "HTUniverse.h"

class BHUniverse : public HTUniverse {
public:
    explicit BHUniverse(double dt);

    void updateAccels() override;
};


#endif //GRAVITYSIMULATOR_BHUNIVERSE_H
