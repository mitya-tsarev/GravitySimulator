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
    std::vector<std::string> words;
    getline(inputfile, line);
    std::cout << line;
    boost::split(words, line, boost::is_any_of("\t "));

    if (words.size() != 2) {
        std::runtime_error e((std::string("Error on line 1: ") + line +
                              std::string(". The first line should specify the method")).c_str());
        throw e;
    }

    if (words[0] != "method") {
        std::runtime_error e((std::string("Error on line 1: ") + line +
                              std::string(". The first line should specify the method")).c_str());
        throw e;
    }


    if (words[1] == "BarnesHutt")
        u = new BarnesHutUniverse(0);
    if (words[1] == "RungeKutta")
        u = new SimpleUniverse(0);


    while (getline(inputfile, line)) {
        std::cout << line << '\n';
    }
    //addBody();
}

std::vector<std::string> getwords(std::string sentence) {
    std::istringstream iss(sentence);
    std::vector<std::string> tokens;
    copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         back_inserter(tokens));
    for (auto it = tokens.begin(); it != tokens.end(); it++) {
        if (*it == "") {
            tokens.erase(it);
            it--;
        }
    }
    return tokens;
}

void Simulator::addBody(double m, double x, double y, double z, double vx, double vy, double vz) {
    u->addBody(mathing::Vec4(x, y, z, 0), mathing::Vec4(vx, vy, vz, 0), m);
}

void Simulator::simulate() {
    //auto list = u->getPosList();
    //std::cout << "x position of first body is " << list[0].x << std::endl;
    std::cout << "179\n";
}
