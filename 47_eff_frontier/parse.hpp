#ifndef __PARSE_HPP__
#define __PARSE_HPP__

#include "asset.hpp"
#include "portfolio.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;

void splitString(std::string& s, std::vector<std::string>& v, std::string& c);
std::vector<Asset> readUniverse(char* filename,int &num);
MatrixXd readCorrMatrix(char* filename,int num);
double UnrestrictOptimal(Portfolio &P,double &ret); 
double RestrictOptimal(Portfolio &P,double &ret);
#endif