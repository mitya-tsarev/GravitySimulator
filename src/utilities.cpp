#include "../include/utilities.h"
#include <random>

double utilities::uniform(double a, double b) {
    return a + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(b - a)));
}
