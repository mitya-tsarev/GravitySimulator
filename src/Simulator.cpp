#include "../include/Simulator.h"

#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iterator>
#include <boost/algorithm/string.hpp>


Simulator::Simulator(std::ifstream &inputfile) {
    std::string line;
    std::string method;
    std::vector<std::string> words;
    getline(inputfile, method);
    getline(inputfile, line);
    boost::split(words, line, boost::is_any_of("\t "));
    double dt = std::stod(words[1]);
    boost::split(words, method, boost::is_any_of("\t "));

    if (words[1] == "BarnesHutt") {
        int m = 1;
        if (words[2] == "Euler")
            m = 0;
        u = new BarnesHutUniverse(dt, m);
    }
    if (words[1] == "Simple") {
        int m = 1;
        if (words[2] == "Euler")
            m = 0;
        u = new SimpleUniverse(dt, m);
    }

    while (getline(inputfile, line)) {
        boost::split(words, line, boost::is_any_of("\t "));
        if (words[0] == "create") {
            if (words[1] == "body") {
                u->addBody(mathing::Vec4(std::stod(words[3]), std::stod(words[4]), std::stod(words[5]), 0),
                           mathing::Vec4(std::stod(words[6]), std::stod(words[7]), std::stod(words[8]), 0),
                           std::stod(words[2]));
            }
        }
        if (words[0] == "run")
            runtime = std::stod(words[1]);
        if (words[0] == "nframes")
            nframes = std::stod(words[1]);
    }
}

void Simulator::simulate() {
    for (int i = 0; i < nframes; i++) {
        auto list = u->getPosList();
        std::cout << list[1].x << ", " << list[1].y << '\n';
        u->update(runtime / nframes);
    }
}
