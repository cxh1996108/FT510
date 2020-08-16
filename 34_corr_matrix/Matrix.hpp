#ifndef __T_MATRIX_HPP__
#define __T_MATRIX_HPP__

#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <iomanip>
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix():numRows(0), numColumns(0) {}
  Matrix(int r, int c);
  Matrix(const Matrix<T> & rhs):numRows(rhs.numRows),numColumns(rhs.numColumns),rows(rhs.rows) {}
  Matrix<T> & operator=(const Matrix<T> & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix<T> & rhs) const;
  Matrix<T> operator+(const Matrix<T> & rhs) const;
};
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs);
template <typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c), rows(r) {
  for(int i=0;i<numRows;i++){
    std::vector<T> temp(numColumns);
    rows[i] = temp;
  }
}
//  An assignment operator, which makes a deep copy.
template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  if(this != &rhs){
 	  numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
  }
  return *this;
}
//  Returns the number of rows.
template <typename T>
int Matrix<T>::getRows() const {
  return numRows;
}
//  Returns the number of columns.
template <typename T>
int Matrix<T>::getColumns() const {
  return numColumns;
}
/*  Uses assert() to check that index is valid and returns a reference
    to the requested row.*/
template <typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert(index>=0);
  assert(index<numRows);
  return rows[index];
}
template <typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert(index>=0);
  assert(index<numRows);
  return rows[index];
}
/*  Compares two matrices for equality. The matrices are equal if they
    have the same number of rows, the same number of columns, and each
    element is the same as the corresponding element in the other
    matrix.*/
template <typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if(numRows!=rhs.numRows || numColumns!=rhs.numColumns){
    return false;
  }
  if(rows != rhs.rows){ 
      return false;
  }
  return true;
}
/*  Assert()s that this and rhs have the same dimensions and returns a
    matrix (also the same dimensions as this and rhs) whose elements
    are the sum of the corresponding elements of this matrix and rhs
    (does matrix addition). */
template <typename T>  
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert(numRows == rhs.numRows);
  assert(numColumns == rhs.numColumns);
  Matrix<T> s(numRows,numColumns);
  for(int i=0;i<numRows;i++){
    for(int j=0;j<numColumns;j++){
      s.rows[i][j] = rows[i][j] + rhs.rows[i][j];
    }
  }
  return s;
}
//Print
template <typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if(rhs.getRows()==0){
    s<<"[  ]";
    return s;
  }
  int i=0;
  int j=0;
  std::cout.setf(std::ios::fixed);
  s<<std::setprecision(4)<<"[ "<<(rhs[i])[j];
  for(j=1;j<rhs.getColumns();j++){
    if((rhs[i])[j]>=0){
      s<<std::setprecision(4)<<", "<<(rhs[i])[j];  
    }
    else{
      s<<std::setprecision(4)<<","<<(rhs[i])[j];  
    }
  }
  s<<std::endl;
  for(i=1;i<rhs.getRows();i++){
    if((rhs[i])[0]>=0){
      s<<" ";
    }
    s<<" ";
    int j=0;
    s<<std::setprecision(4)<<(rhs[i])[j];
    for(j=1;j<rhs.getColumns();j++){
      if((rhs[i])[j]>=0){
        s<<std::setprecision(4)<<", "<<(rhs[i])[j];  
      }
      else{
        s<<std::setprecision(4)<<","<<(rhs[i])[j];  
      }
    }
    if(i==rhs.getRows()-1){
      s<<"]"<<std::endl;  
    }
    else{
      s<<std::endl; 
    }
  }
  std::cout.unsetf(std::ios::fixed);
  return s;
}

#endif
