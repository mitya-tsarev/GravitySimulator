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
            words.pop_back();
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

//std::pair<mathing::Vec4, mathing::Vec4> disk(double )
