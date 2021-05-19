#ifndef TEST_PY_UTILITIES_H
#define TEST_PY_UTILITIES_H


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "vector.h"

class utilities {
public:
    constexpr const static double SMOOTH = 0.5; // TODO move it from here
    static double uniform(double a, double b);

    static std::vector<std::string> splitString(std::string s, const std::string &delimiter_list);

    static mathing::Vec4 rotate(mathing::Vec4 from, mathing::Vec4 to, mathing::Vec4 r);

    static std::vector<std::vector<std::string>> getallwords(std::ifstream &inputfile);

    static std::pair<mathing::Vec4, mathing::Vec4> disk(const mathing::Vec4& center, const mathing::Vec4& velocity, mathing::Vec4 normal, double centralmass, double radius,
         double height, double clustermass, double G);
};


#endif //TEST_PY_UTILITIES_H
