#ifndef __PORTFOLIO_HPP__
#define __PORTFOLIO_HPP__

#include "asset.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;

class Portfolio {
  public:
    int n;//the number of Assets
    VectorXd weight;//a vector of weights
    std::vector<Asset> A;//a list of Assets
    double sigma;//portfolio volatility
    double ror;//rate of return
    MatrixXd Corr;//correlation matrix
  public:
    Portfolio(){}
    void calculateROR(){
      int sum = 0;
      for(int i=0;i<n;i++){
        sum += weight(i)*A[i].avr;
      }
      ror = sum;
    }
    void calculateSigma(){     
      double sum = 0;
      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          sum += weight(i)*weight(j)*Corr(i,j)*A[i].sigma*A[j].sigma;
        }
      }
      sigma = std::sqrt(sum);
    } 
    ~Portfolio(){}
};

#endif
