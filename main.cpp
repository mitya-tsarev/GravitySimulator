#include <fstream>
#include <string>

#include "include/Simulator.h"

int main() {
    std::ifstream inputfile;
    inputfile.open("../input");
    try {
        auto *simulator = new Simulator(inputfile);
        simulator->simulate();
        delete simulator;
    }
    catch (const std::exception &e) {
        e.what();
        return 0;
    }
    return 0;
}