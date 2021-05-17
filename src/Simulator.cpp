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
            nframes = std::stoi(words[1]);
        if (words[0] == "save") {
            if (words[1] == "perbody") {
                perBodyOutputFilename = words[2];
                for (int i = 3; i < words.size(); i++)
                    savePerBody.push_back(words[i]);
            }
            if (words[1] == "global") {
                globalOutputFilename = words[2];
                for (int i = 3; i < words.size(); i++)
                    saveGlobal.push_back(words[i]);
            }
        }
    }
}

void Simulator::write_vtk(const std::string &filename) {
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
    for (const auto &p : positions) {
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

    if (!savePerBody.empty()) {
        output << "<PointData  Scalars=\" smth \">\n";
        for (const auto &quantity : savePerBody) {
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
    std::ofstream output;
    output.open("../" + globalOutputFilename);
    for (auto s : saveGlobal) {
        std::cout << s << " ";
        output << s << " ";
    }
    std::cout << '\n';
    output << '\n';
    for (int i = 0; i <= nframes; i++) {
        for (const auto& quantity : saveGlobal) {
            if (quantity == "time") {
                std::cout << runtime * i / nframes << "     ";
                output << runtime * i / nframes << "     ";
            }
            if (quantity == "potentialenergy") {
                double pe = getPotEng();
                std::cout << pe << "   ";
                output << pe << "   ";
            }
            if (quantity == "kineticenergy") {
                double ke = getKinEng();
                std::cout << ke << "   ";
                output << ke << "   ";
            }
            if (quantity == "totalenergy") {
                double eng = getKinEng() + getPotEng();
                std::cout << eng << "   ";
                output << eng << "  ";
            }
            if (quantity.substr(0, 8) == "momentum") {
                auto momentum = getMomentum();
                if (quantity.substr(8, 9) == "x") {
                    std::cout << momentum.x << "   ";
                    output << momentum.x << "  ";
                }
                if (quantity.substr(8, 9) == "y") {
                    std::cout << momentum.y << "   ";
                    output << momentum.y << "  ";
                }
                if (quantity.substr(8, 9) == "z") {
                    std::cout << momentum.z << "   ";
                    output << momentum.z << "  ";
                }
            }
            if (quantity.substr(0, 10) == "barycenter") {
                auto bary = getBarycenter();
                if (quantity.substr(10, 11) == "x") {
                    std::cout << bary.x << "   ";
                    output << bary.x << "  ";
                }
                if (quantity.substr(10, 11) == "y") {
                    std::cout << bary.y << "   ";
                    output << bary.y << "  ";
                }
                if (quantity.substr(10, 11) == "z") {
                    std::cout << bary.z << "   ";
                    output << bary.z << "  ";
                }
            }
        }
        std::cout << '\n';
        output << '\n';
        write_vtk("../" + perBodyOutputFilename + std::to_string(i));
        u->update(runtime / nframes);
    }
    output.close();
}

std::vector<double> Simulator::getPerBodyVels() {
    std::vector<double> ans;
    auto vectVels = u->getVelList();
    ans.reserve(vectVels.size());
    for (auto v : vectVels)
        ans.push_back(v.Length3());
    return ans;
}

double Simulator::getPotEng() {
    double pe = 0;
    auto pos = u->getPosList();
    auto mas = u->getMassList();
    int n = mas.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pe -= u->G * mas[i] * mas[j] / (pos[i] - pos[j]).Length3();
        }
    }
    return pe;
}

double Simulator::getKinEng() {
    double ke = 0;
    auto vels = u->getVelList();
    auto mas = u->getMassList();
    int n = mas.size();
    for (int i = 0; i < n; i++) {
        double v = vels[i].Length3();
        ke += mas[i] * v * v / 2;
    }
    return ke;
}

mathing::Vec4 Simulator::getMomentum() {
    mathing::Vec4 momentum;
    auto vels = u->getVelList();
    auto mas = u->getMassList();
    int n = mas.size();
    for (int i = 0; i < n; i++) {
        momentum += mas[i] * vels[i];
    }
    return momentum;
}

mathing::Vec4 Simulator::getBarycenter() {
    mathing::Vec4 bary;
    double totalm = 0;
    auto pos = u->getVelList();
    auto mas = u->getMassList();
    int n = mas.size();
    for (int i = 0; i < n; i++) {
        bary += mas[i] * pos[i];
        totalm += mas[i];
    }
    bary = bary / totalm;
    return bary;
}
