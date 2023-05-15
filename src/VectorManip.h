#ifndef VECTORMANIP_H
#define VECTORMANIP_H

#include <vector>
#include <string>
#include <iostream>
#include <cstring>

namespace VectorManip {

int ChooseFromVector(const std::vector<std::string> &choices, std::string option);
void RemoveFromVector(std::vector<std::string> &vec, std::string option);
bool IsValueInVector(const std::vector<std::string> &vec, const std::string &value);

}
#endif