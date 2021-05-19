#ifndef TEST_PY_UTILITIES_H
#define TEST_PY_UTILITIES_H


#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class utilities {
public:
    constexpr const static double SMOOTH = 0.5; // TODO move it from here
    static double uniform(double a, double b);
    static std::vector<std::string> splitString(std::string s, const std::string &delimiter_list);
    static std::vector<std::vector<std::string>> getallwords(std::ifstream &inputfile);
};


#endif //TEST_PY_UTILITIES_H
