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
    double dt = std::stoi(words[1]);
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
    }
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
