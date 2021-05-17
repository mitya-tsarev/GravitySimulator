#include "../include/Simulator.h"

#include <iostream>
#include <fstream>
#include <string>


// split string by any of the characters in the given string
std::vector<std::string> splitString(std::string s, const std::string &delimiter_list) {
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

    if (words[1] == "BarnesHut") {
        int m = 1;
        double tau = stod(words[3]);
        if (words[2] == "Euler")
            m = 0;
        u = new BarnesHutUniverse(dt, tau, m);
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
            if (words[1] == "cluster")
                addCluster(words);
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
        for (const auto &quantity : saveGlobal) {
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

void Simulator::addCluster(std::vector<std::string> words) {
    int N = 1;
    std::string distx = "constant";
    std::string disty = "constant";
    std::string distz = "constant";
    std::vector<double> paramsx;
    std::vector<double> paramsy;
    std::vector<double> paramsz;
    std::string distvx = "constant";
    std::string distvy = "constant";
    std::string distvz = "constant";
    std::vector<double> paramsvx;
    std::vector<double> paramsvy;
    std::vector<double> paramsvz;
    std::string distmass = "constant";
    std::vector<double> paramsm;
    for (int i = 2; i < words.size(); i++) {
        if (words[i] == "n") {
            N = stoi(words[i + 1]);
            i++;
            continue;
        }
        if (words[i] == "mass") {
            distmass = words[i + 1];
            if (distmass == "constant") {
                paramsm.push_back(stod(words[i + 2]));
                i += 2;
                continue;
            }
            if (distmass == "uniform") {
                paramsm.push_back(stod(words[i + 2]));
                paramsm.push_back(stod(words[i + 3]));
                i += 3;
                continue;
            }
        }
        if (words[i] == "x") {
            distx = words[i + 1];
            if (distx == "constant") {
                paramsx.push_back(stod(words[i + 2]));
                i += 2;
                continue;
            }
            if (distx == "uniform") {
                paramsx.push_back(stod(words[i + 2]));
                paramsx.push_back(stod(words[i + 3]));
                i += 3;
                continue;
            }
        }
        if (words[i] == "y") {
            disty = words[i + 1];
            if (disty == "constant") {
                paramsy.push_back(stod(words[i + 2]));
                i += 2;
                continue;
            }
            if (disty == "uniform") {
                paramsy.push_back(stod(words[i + 2]));
                paramsy.push_back(stod(words[i + 3]));
                i += 3;
                continue;
            }
        }
        if (words[i] == "z") {
            distz = words[i + 1];
            if (distz == "constant") {
                paramsz.push_back(stod(words[i + 2]));
                i += 2;
                continue;
            }
            if (distz == "uniform") {
                paramsz.push_back(stod(words[i + 2]));
                paramsz.push_back(stod(words[i + 3]));
                i += 3;
                continue;
            }
        }
        if (words[i] == "vx") {
            distvx = words[i + 1];
            if (distvx == "constant") {
                paramsvx.push_back(stod(words[i + 2]));
                i += 2;
                continue;
            }
            if (distvx == "uniform") {
                paramsvx.push_back(stod(words[i + 2]));
                paramsvx.push_back(stod(words[i + 3]));
                i += 3;
                continue;
            }
        }
        if (words[i] == "vy") {
            distvy = words[i + 1];
            if (distvy == "constant") {
                paramsvy.push_back(stod(words[i + 2]));
                i += 2;
                continue;
            }
            if (distvy == "uniform") {
                paramsvy.push_back(stod(words[i + 2]));
                paramsvy.push_back(stod(words[i + 3]));
                i += 3;
                continue;
            }
        }
        if (words[i] == "vz") {
            distvz = words[i + 1];
            if (distvz == "constant") {
                paramsvz.push_back(stod(words[i + 2]));
                i += 2;
                continue;
            }
            if (distvz == "uniform") {
                paramsvz.push_back(stod(words[i + 2]));
                paramsvz.push_back(stod(words[i + 3]));
                i += 3;
                continue;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        double m_, x_, y_, z_, vx_, vy_, vz_;
        if (distmass == "uniform")
            m_ = utilities::uniform(paramsm[0], paramsm[1]);
        if (distmass == "constant")
            m_ = paramsm[0];
        if (distx == "uniform")
            x_ = utilities::uniform(paramsx[0], paramsx[1]);
        if (distx == "constant")
            x_ = paramsx[0];
        if (disty == "uniform")
            y_ = utilities::uniform(paramsy[0], paramsy[1]);
        if (disty == "constant")
            y_ = paramsy[0];
        if (distz == "uniform")
            z_ = utilities::uniform(paramsz[0], paramsz[1]);
        if (distz == "constant")
            z_ = paramsz[0];
        if (distvx == "uniform")
            vx_ = utilities::uniform(paramsvx[0], paramsvx[1]);
        if (distvx == "constant")
            vx_ = paramsvx[0];
        if (distvy == "uniform")
            vy_ = utilities::uniform(paramsvy[0], paramsvy[1]);
        if (distvy == "constant")
            vy_ = paramsvy[0];
        if (distvz == "uniform")
            vz_ = utilities::uniform(paramsvz[0], paramsvz[1]);
        if (distvz == "constant")
            vz_ = paramsvz[0];

        u->addBody(mathing::Vec4(x_, y_, z_, 0), mathing::Vec4(vx_, vy_, vz_, 0), m_);
    }
}
