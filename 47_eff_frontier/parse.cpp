#include "asset.hpp"
#include "portfolio.hpp"
#include "parse.hpp"
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
//Split string with delimiter
void splitString(std::string& s, std::vector<std::string>& v, std::string& c){
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
//Read universe
std::vector<Asset> readUniverse(char* filename,int &num){
  std::vector<Asset> A;
  std::ifstream ifs(filename);
  if(!ifs.is_open()){
    perror("Could not open universe file");
   	exit(EXIT_FAILURE);
  }
  std::string line;
  std::string c = ",";  
  while(std::getline(ifs,line)){
    std::vector<std::string> t;
    splitString(line,t,c);
    if(t.size() != 3){
      perror("Assets have wrong format");//handle non-numeric value
   	  exit(EXIT_FAILURE);
    }
    Asset temp;
    temp.name = t[0];
    if(atof(t[1].c_str())==0.0 || atof(t[2].c_str())==0.0){
      perror("Assets have non-numeric value");//handle non-numeric value
   	  exit(EXIT_FAILURE);
    }
    temp.avr = atof(t[1].c_str());
    temp.sigma = atof(t[2].c_str());
    num++;
    A.push_back(temp);
  }
  if(num == 0){
    perror("Universe file is empty");//handle empty file
    exit(EXIT_FAILURE);
  }
  return A;
}
//Read correlation matrix
MatrixXd readCorrMatrix(char* filename,int num){
  std::ifstream ifs(filename);
  if(!ifs.is_open()){
    perror("Could not open correlation file");
   	exit(EXIT_FAILURE);
  }

  MatrixXd Corr(num,num);
  std::string line;
  std::string c = ","; 
  int i=0;
  while(std::getline(ifs,line)){
    if(i == num){
      perror("Dimension of correlation matrix is greater than the number of assets");//handle larger matrix while less assets
      exit(EXIT_FAILURE);
    }
    std::vector<std::string> t;
    splitString(line,t,c);
    if(t.size() != (size_t)num){
      perror("Dimension of correlation matrix is not the same as the number of assets");//handle different dimensions
      exit(EXIT_FAILURE);
    }
    for(int j=0;j<num;j++){
      if(atof(t[j].c_str())==0.0){
        perror("Correlation matrix has non-numeric value");//handle non-numeric value
   	    exit(EXIT_FAILURE);
      }
      Corr(i,j) = atof(t[j].c_str());
    }
    i++;
  }
  if(i == 0){
    perror("Correlation file is empty");//handle empty file
    exit(EXIT_FAILURE);
  }
  for(int i=0;i<num;i++){//Actually correlation matrix shoule be positive semidefinite
    for(int j=0;j<=i;j++){
      if(fabs(Corr(i,j) - Corr(j,i)) > 0.0001 || fabs(Corr(i,j)) > 1.0001){
        perror("Correlation matrix has wrong mathematical format");//handle wrong format
        exit(EXIT_FAILURE);
      }
    }
    if(fabs(Corr(i,i) - 1) > 0.0001){
      perror("Corr(i,i) does not equal to 1");//handle Corr(i,i) != 1
      exit(EXIT_FAILURE);
    }
  }
  return Corr;
}
//Unrestricted case: Optimal portfolio volatility given expected portfolio return
double UnrestrictOptimal(Portfolio &P,double &ret){
  int n = P.n;
  MatrixXd A1 = MatrixXd::Ones(1,n);
  MatrixXd A2(1,n);
  for(int i=0;i<n;i++){
    A2(i) = P.A[i].avr;
  }
  MatrixXd A(2,n);
  A<<A1,A2;//Initialize A
  MatrixXd b1 = MatrixXd::Zero(n,1);
  MatrixXd b2(2,1);
  b2<<1,ret;
  MatrixXd B(n+2,1);
  B<<b1,b2;//Initialize B
  MatrixXd Cov(n,n);//Covariance Matrix
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      Cov(i,j) = P.A[i].sigma * P.Corr(i,j) * P.A[j].sigma;
    }
  }
  MatrixXd O = MatrixXd::Zero(2,2);//Initialize O
  MatrixXd K(n+2,n+2);//The equation is KX = B  
  K<<Cov,A.transpose(),A,O;//Initialize K
  VectorXd X(n+2,1);
  X = K.fullPivHouseholderQr().solve(B);//Solve the equation
  P.weight = X.head(n);
  P.calculateSigma();
  return P.sigma;
}
//Restricted case: Optimal portfolio volatility given expected portfolio return
double RestrictOptimal(Portfolio &P,double &ret){
  int n = P.n;
  MatrixXd A1 = MatrixXd::Ones(1,n);
  MatrixXd A2(1,n);
  for(int i=0;i<n;i++){
    A2(i) = P.A[i].avr;
  }
  MatrixXd A(2,n);
  A<<A1,A2;//Initialize A
  MatrixXd b1 = MatrixXd::Zero(n,1);
  MatrixXd b2(2,1);
  b2<<1,ret;
  MatrixXd B(n+2,1);
  B<<b1,b2; //Initialize B
  MatrixXd Cov(n,n);//Covariance Matrix
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      Cov(i,j) = P.A[i].sigma * P.Corr(i,j) * P.A[j].sigma;
    }
  }
  MatrixXd O = MatrixXd::Zero(2,2);
  MatrixXd K(n+2,n+2);//The equation is KX = B  
  K<<Cov,A.transpose(),A,O;//Initialize K
  VectorXd X(n+2,1);
  X = K.fullPivHouseholderQr().solve(B);//Use the direct solution method to find the unrestricted weights
  MatrixXd AA = A;
  MatrixXd BB = B;
  VectorXd XX = X;
  for(int i=1;;i++){//loop until there are no new negative weights
    int flag = 1;
    MatrixXd C;//constraint matrix
    int k=0;
    for(int j=0;j<n;j++){//Check for any weights that are negative
      if(XX(j) < 0){//use 0.00001 instead of 0 will be good enough and quicker
        MatrixXd T = MatrixXd::Zero(n,1);//temp matrix
        T(j,0) = 1;
        MatrixXd temp = C;
        C.resize(n,k+1);
        if(k==0){
          C<<T;  
        }
        else{
          C<<temp,T;//add constraints that weights be exactly zero
        }
        flag = 0;
        k++;
      }
    }
    if(flag == 1){//Stop if there are no new negative weights
      break;
    }
    MatrixXd T;//temp matrix
    T = AA;
    AA.resize(T.rows() + C.cols(),n);//add rows to matrix A for new constraints
    AA<<T,C.transpose();
    T = BB;
    BB.resize(T.rows() + C.cols(),1);
    BB<<T,MatrixXd::Zero(C.cols(),1);//add rows to vector b for new constraints
    MatrixXd OO = MatrixXd::Zero(AA.rows(),AA.rows());
    MatrixXd KK(Cov.rows() + AA.rows(),Cov.rows() + AA.rows());
    KK<<Cov,AA.transpose(),AA,OO;
    XX = KK.fullPivHouseholderQr().solve(BB);//direct solution method to find the weights
  }
  P.weight = XX.head(n);
  P.calculateSigma();
  return P.sigma;
}