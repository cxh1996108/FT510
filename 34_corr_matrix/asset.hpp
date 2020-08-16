#ifndef __ASSET_HPP__
#define __ASSET_HPP__

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
class Asset {
  public:
    std::string name;
    std::vector<double> price;
    std::vector<double> ror;//time series rate of return
    double avr;//average return
    double sigma;//standard deviation
    int n;//the number of dates
  public:
    Asset(){}
    ~Asset(){}
    void calculateROR();
    void calculateAvrSigma();
    friend Asset* readData(char* s);
};

#endif
