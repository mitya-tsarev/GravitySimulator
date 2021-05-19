#include <fstream>
#include <string>

#include "include/Simulator.h"

int main(int argc, char *argv[]) {
    std::cout.precision(8);
    std::ifstream inputfile;
    if (argc == 1) {
        inputfile.open("../input");
    } else
        inputfile.open(std::string(argv[1]));
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