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

void Simulator::write_vtk(std::string filename) {
    auto positions = u->getPosList();
    std::ofstream output;
    output.open(filename + ".vtu");
    output << "<?xml version=\"1.0\"?>\n";
    output << "<VTKFile type=\"UnstructuredGrid\"  version=\"0.1\"  >\n";
    output << "<UnstructuredGrid>\n";
    output << "<Piece  NumberOfPoints=\"" + std::to_string(positions.size()) +
              "\" NumberOfCells=\"" + std::to_string(positions.size()) + "\">\n";
    output << "<Points>\n";
    output << "<DataArray  type=\"Float64\"  NumberOfComponents=\"3\"  format=\"ascii\">";
    for (auto p : positions) {
        output << p.x << " " << p.y << " " << p.z << "  ";
    }
    output << "</DataArray>\n";
    output << "</Points>\n";
    output << "<Cells>\n";
    output << "<DataArray  type=\"UInt32\"  Name=\"connectivity\"  format=\"ascii\">\n";
    for (int i = 0; i < positions.size(); i++) {
        output << i << " " << i << "    ";
    }
    output << "</DataArray>\n";
    output << "<DataArray  type=\"UInt32\"  Name=\"offsets\"  format=\"ascii\">\n";
    for (int i = 0; i < positions.size(); i++) {
        output << 2 * i + 2 << " ";
    }
    output << "</DataArray>\n";
    output << "<DataArray  type=\"UInt32\"  Name=\"types\"  format=\"ascii\">\n";
    for (int i = 0; i < positions.size(); i++) {
        output << "1 ";
    }
    output << "</DataArray>\n";
    output << "</Cells>\n";
    output << "</Piece>\n";
    output << "</UnstructuredGrid>\n";
    output << "</VTKFile>\n";

    output.close();
}

void Simulator::simulate() {
    for (int i = 0; i <= nframes; i++) {
        auto list = u->getPosList();
        auto vels = u->getVelList();
        std::cout << list[1].x << ", " << list[1].y << ", " << list[1].Length3() << '\n';
        write_vtk("../system" + std::to_string(i));
        u->update(runtime / nframes);
    }
}
