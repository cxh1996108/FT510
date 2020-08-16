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
    double avr;//expected return
    double sigma;//standard deviation
  public:
    Asset(){}
    ~Asset(){}
};

#endif