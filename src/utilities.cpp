#include "../include/utilities.h"
#include <random>
#include "../include/vector.h"
#include "../include/Simulator.h"

double utilities::uniform(double a, double b) {
    return a + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (b - a)));
}

// split string by any of the characters in the given string
std::vector<std::string> utilities::splitString(std::string s, const std::string &delimiter_list) {
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

std::vector<std::vector<std::string>> utilities::getallwords(std::ifstream &inputfile) {
    std::vector<std::vector<std::string>> ans;
    std::string line;
    while (getline(inputfile, line)) {
        std::vector<std::string> words;
        std::vector<std::string> curwords = splitString(line, "\t ");
        words.insert(words.end(), curwords.begin(), curwords.end());
        if (words.empty())
            continue;
        if (words.front()[0] == '#')
            continue;

        if (words.back().back() != '\\') {
            ans.push_back(words);
            continue;
        } else {
            std::string last = words.back();
            words.pop_back();
            if (last != "\\")
                words.push_back(last.substr(0, last.size() - 1));
        }
        while (getline(inputfile, line)) {
            curwords = splitString(line, "\t ");
            words.insert(words.end(), curwords.begin(), curwords.end());
            if (words.empty())
                continue;
            if (words.front()[0] == '#') {
                words.clear();
                continue;
            }
            if (words.back().back() != '\\') {
                ans.push_back(words);
                break;
            }
        }
    }
    return ans;
}

std::pair<mathing::Vec4, mathing::Vec4>
utilities::disk(const mathing::Vec4 &center, const mathing::Vec4 &velocity, mathing::Vec4 normal, double centralmass,
                double radius, double height, double clustermass, double G) {
    double z = uniform(-height / 2, height / 2);
    double phi = uniform(0, 2 * M_PI);
    double r = sqrt(uniform(0, 1)) * radius;
    mathing::Vec4 pos(r * cos(phi), r * sin(phi), z, 0);
    normal.Normalize3();
    mathing::Vec4 ez(0, 0, 1, 0);
    pos = rotate(ez, normal, pos);
    double v = sqrt(G / r * (centralmass + clustermass * r * r / radius / radius));
    mathing::Vec4 vel = mathing::Vec4::Cross(normal, pos) * v / pos.Length3();
    return std::pair<mathing::Vec4, mathing::Vec4>(pos + center, vel + velocity);
}

mathing::Vec4 utilities::rotate(mathing::Vec4 from, mathing::Vec4 to, mathing::Vec4 r) {
    mathing::Vec4 axis = mathing::Vec4::Cross(from, to);
    const double cosA = mathing::Vec4::Dot3(from, to);
    const double k = 1 / (1 + cosA);

    double x = mathing::Vec4::Dot3(mathing::Vec4((axis.x * axis.x * k) + cosA,
                                                 (axis.y * axis.x * k) - axis.z,
                                                 (axis.z * axis.x * k) + axis.y), r);
    double y = mathing::Vec4::Dot3(mathing::Vec4((axis.x * axis.y * k) + axis.z,
                                                 (axis.y * axis.y * k) + cosA,
                                                 (axis.z * axis.y * k) - axis.x), r);
    double z = mathing::Vec4::Dot3(mathing::Vec4((axis.x * axis.z * k) - axis.y,
                                                 (axis.y * axis.z * k) + axis.x,
                                                 (axis.z * axis.z * k) + cosA), r);
    return mathing::Vec4(x, y, z, 0);
}

