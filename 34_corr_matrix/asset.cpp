#include "Matrix.hpp"
#include "asset.hpp"
#include "parse.hpp"
#include <iostream>
#include <cmath>
void Asset::calculateROR(){
  for(int i=0;i<n-1;i++){
    ror.push_back((price[i+1] - price[i])/price[i]);
  }
}
void Asset::calculateAvrSigma(){
  double sum=0;
  for(int i=0;i<n-1;i++){
    sum = sum + ror[i];
  }
  avr = sum/(n-1);
  sum = 0; 
  for(int i=0;i<n-1;i++){
    sum = sum + (ror[i] - avr)*(ror[i] - avr);
  }
  sigma = std::sqrt(sum/(n-2));
}

