#ifndef GRAVITYSIMULATOR_SIMPLEUNIVERSE_H
#define GRAVITYSIMULATOR_SIMPLEUNIVERSE_H

#include "LinearTimeUniverse.h"

class SimpleUniverse : public LinearTimeUniverse {
    public:
        explicit SimpleUniverse(double dt);

        void updateAccels() override;
};



#endif //GRAVITYSIMULATOR_SIMPLEUNIVERSE_H
