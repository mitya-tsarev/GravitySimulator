#include "../include/Simulator.h"

#include <iostream>
#include <fstream>
#include <string>


// split string by any of the characters in the given string
std::vector<std::string> splitString(std::string s, const std::string& delimiter_list) {

    std::vector<std::string> words;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find_first_of(delimiter_list)) != std::string::npos) {
        token = s.substr(0, pos);
        if (!token.empty()) words.push_back(token);
        s.erase(0, pos + 1);
    }
    if (!s.empty()) words.push_back(s);
    return words;
}


Simulator::Simulator(std::ifstream &inputfile) {
    std::string line;
    std::string method;
    std::vector<std::string> words;
    getline(inputfile, method);
    getline(inputfile, line);
    words = splitString(line, "\t ");
    double dt = std::stod(words[1]);
    words = splitString(method, "\t ");

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
        words = splitString(line, "\t ");
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
        if (words[0] == "save") {
            perBodyOutputFilename = words[1];
            for (int i = 2; i < words.size(); i++)
                save_params.push_back(words[i]);
        }
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

    if (!save_params.empty()) {
        output << "<PointData  Scalars=\" smth \">\n";
        for (auto quantity : save_params) {
            output << "<DataArray  type=\"Float64\"  Name=\"" + quantity + "\"  format=\"ascii\">";
            std::vector<double> vals;
            if (quantity == "mass")
                vals = u->getMassList();
            if (quantity == "velocity")
                vals = getPerBodyVels();
            for (auto v : vals)
                output << v << " ";
            output << "</DataArray >\n";
        }
        output << "</PointData >\n";
    }

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
        write_vtk("../" + perBodyOutputFilename + std::to_string(i));
        u->update(runtime / nframes);
    }
}

std::vector<double> Simulator::getPerBodyVels() {
    std::vector<double> ans;
    auto vectVels = u->getVelList();
    for (auto v : vectVels)
        ans.push_back(v.Length3());
    return ans;
}
