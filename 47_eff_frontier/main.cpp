#include "asset.hpp"
#include "parse.hpp"
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
#include <iomanip>
#include <unistd.h>
using namespace Eigen;
int main(int argc, char ** argv){
  if (argc != 3 && argc !=4) {
    fprintf(stderr, "Input Error\n");
    return EXIT_FAILURE;
  }
  if(argc ==4 && strlen(argv[1]) != 2){
      std::cerr<<"Option size or position is wrong";//Cannot allow something like -rabcdefghijk
      return EXIT_FAILURE;
  }
//(1) check whether "-r" is passed
  int opt;
  bool r = false;
  while ((opt = getopt(argc, argv, "r")) != -1){
    switch(opt){
      case 'r':
        r = true;
        break;
      case '?':
        std::cerr<<"Option is wrong";
        return EXIT_FAILURE;
    }
  }
//(2) Read universe
  int num = 0;//the number of assets
  std::vector<Asset> A;
  MatrixXd Corr;
  if(r == true){
    A = readUniverse(argv[2],num);
    Corr = readCorrMatrix(argv[3],num);
  }
  else{
    A = readUniverse(argv[1],num);
    Corr = readCorrMatrix(argv[2],num); 
  }
//(3) Read correlation
  Portfolio P;
  P.n = num;
  P.A = A;
  P.Corr = Corr;
//(4) Step 1: Unrestricted case: return level between 1% and 26% in 1% increments.
  std::cout<<"ROR,volatility"<<std::endl;
  std::cout.setf(std::ios::fixed);
  if(r == false){
    for(double l = 0.01;l <= 0.265;l += 0.01){
      std::cout<<std::fixed<<std::setprecision(1)<<l*100<<"%,";
      std::cout<<std::fixed<<std::setprecision(2)<<UnrestrictOptimal(P,l)*100<<"%"<<std::endl;
    }
  }
//(5) Step 2: Restricted case: return level between 1% and 26% in 1% increments.
  if(r == true){
    for(double l = 0.01;l <= 0.265;l += 0.01){
      std::cout<<std::fixed<<std::setprecision(1)<<l*100<<"%,";
      std::cout<<std::fixed<<std::setprecision(2)<<RestrictOptimal(P,l)*100<<"%"<<std::endl;
    }
  }
  std::cout.unsetf(std::ios::fixed);
  return EXIT_SUCCESS;
}