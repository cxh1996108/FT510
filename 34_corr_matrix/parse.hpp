#ifndef __PARSE_HPP__
#define __PARSE_HPP__

#include "Matrix.hpp"
#include "asset.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
typedef Matrix<double> DoubleMatrix;
//Split string with delimiter
void splitString(std::string& s, std::vector<std::string>& v, std::string& c);
//Read historical price data from a file.
Asset* readData(char* filename,int &num);
//Caclculate the covariance of two assets
double covariance(Asset A,Asset B);
//Caclculate the correlation of two assets
double correlation(Asset A,Asset B);
DoubleMatrix corrMatrix(Asset* A,int num);

#endif