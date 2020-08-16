#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Matrix.hpp"
#include "asset.hpp"
#include "parse.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Input Error\n");
    return EXIT_FAILURE;
  }
  //(1) Read historical price data from a file.
  Asset * A;
  int num;  //the number of assets
  A = readData(argv[1], num);
  //(2) For each asset, calculate the rate of return for each time step.
  for (int i = 0; i < num; i++) {
    A[i].calculateROR();
  }
  //(3) For each asset, calculate the average return and standard deviation.
  for (int i = 0; i < num; i++) {
    A[i].calculateAvrSigma();
  }
  //(4) Calculate the correlation matrix for all the assets.
  DoubleMatrix M;
  M = corrMatrix(A, num);
  //(5) Print the name of assets and the correlation matrix
  for (int i = 0; i < num; i++) {
    std::cout << A[i].name << std::endl;
  }
  std::cout << M << std::endl;
  delete[] A;
  return EXIT_SUCCESS;
}
