#include "Matrix.hpp"
#include "asset.hpp"
#include "parse.hpp"
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
void splitString(std::string& s, std::vector<std::string>& v, std::string& c)
{
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(std::string::npos != pos2)
  {
    v.push_back(s.substr(pos1, pos2-pos1));
 
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}
//Read historical price data from a file.
Asset* readData(char* filename,int &num){
  std::ifstream ifs(filename);
  if(!ifs.is_open()){
    perror("Could not open file");
   	exit(EXIT_FAILURE);
  }
  std::string line;
  std::getline(ifs,line);
  if(line.size() == 0){//handle empty file
    perror("Empty file");
   	exit(EXIT_FAILURE);
  }
  std::vector<std::string> v;
  std::string c = ",";
  splitString(line,v,c);
  num = v.size()-1;//the number of assets
  Asset* A = new Asset[num];
  for(int i=0;i<num;i++){
    A[i].name = v[i+1];
  }
  int n=0;//the number of dates
  std::vector<std::string> t;
  while(std::getline(ifs,line)){
    splitString(line,t,c);
    int t1 = t.size() + 0;
    if(t1 != (num + 1)){//number of prices not the same as assets
      perror("number of prices is not the same as assets");
   	  exit(EXIT_FAILURE);
    }
    if(n==0){//first line has non-numeric
      for(int i=0;i<num;i++){
        if(t[i+1] == "null" || atof(t[i+1].c_str())==0.0){
          perror("first line has non-numeric");
   	      exit(EXIT_FAILURE);
        }
      }
    }
    for(int i=0;i<num;i++){
      if(t[i+1] == "null" || atof(t[i+1].c_str())==0.0){
        double temp = A[i].price.back();
        A[i].price.push_back(temp);
      }
      else{
        A[i].price.push_back(atof(t[i+1].c_str()));//add .c_str()
      }
    }
    n++;
    t.clear();
  }
  if(n <= 2){//only header line;only 2 lines;only 3 lines
    perror("no enough data to calculate");
 	  exit(EXIT_FAILURE);
  }
  for(int i=0;i<num;i++){
    A[i].name = v[i+1];
  }
  for(int i=0;i<num;i++){
    A[i].n = n;
  }
  return A;
}
//Caclculate the covariance of two assets
double covariance(Asset A,Asset B){
  double sum = 0;
  for(int i=0;i<A.n-1;i++){
    sum = sum + (A.ror[i] - A.avr)*(B.ror[i] - B.avr);
  }
  double cov = sum/(A.n-1);
  return cov;
}
//Caclculate the correlation of two assets
double correlation(Asset A,Asset B){
  double cov = covariance(A,B);
  double corr = cov/(A.sigma*B.sigma);
  return corr;
}
DoubleMatrix corrMatrix(Asset* A,int num){
  DoubleMatrix M(num,num);
  for(int i=0;i<num;i++){
    for(int j=0;j<num;j++){
      if(i == j){
        M[i][j] = 1.0;
      }
      else{
        M[i][j] = correlation(A[i],A[j]);
      }
    }
  }
  return M;
}