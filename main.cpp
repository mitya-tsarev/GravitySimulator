#include <iostream>

#include "include/Simulator.h"

int main() {
    auto * simulator = new Simulator("infile");
    simulator -> simulate("outfile", 1);
    return 0;
}