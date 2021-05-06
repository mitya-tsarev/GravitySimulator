#ifndef GRAVITYSIMULATOR_BARNESHUTUNIVERSE_H
#define GRAVITYSIMULATOR_BARNESHUTUNIVERSE_H

#include "LinearTimeUniverse.h"

class BarnesHutUniverse : public LinearTimeUniverse {
public:
    explicit BarnesHutUniverse(double dt);

    void updateAccels() override;
};


#endif //GRAVITYSIMULATOR_BARNESHUTUNIVERSE_H
