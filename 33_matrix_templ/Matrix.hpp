#ifndef __T_MATRIX_HPP__
#define __T_MATRIX_HPP__

#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;//IMPORTANT!!!!!

 public:
  Matrix():numRows(0), numColumns(0) {}
  Matrix(int r, int c);//:numRows(r),numColumns(c),rows(r) {}
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
  //IMPORTANT!!!!!!! //a[i][j] = i + j;
  for(int i=0;i<numRows;i++){
    std::vector<T> temp(numColumns);
    rows[i] = temp;
  }
  //the following does the same 
	/*for (typename std::vector<std::vector<T> >::iterator it = rows.begin(); it != rows.end(); ++it) {
	  	it->resize(c, T());
	}*/
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
      //(s.rows[i]).push_back ( rows[i][j] + rhs.rows[i][j] );WRONG!!!!!
      s.rows[i][j] = rows[i][j] + rhs.rows[i][j];
    }
  }
  return s;
}
/*template <typename T> 
Matrix<T> Matrix<T>::operator +(const Matrix<T>& m) {
	assert(nRows == m.nRows && nCols == m.nCols);
	Matrix<T> ans(nRows, nCols);
	typename std::vector<std::vector<T> >::iterator z;
	typename std::vector<std::vector<T> >::const_iterator x = rows.begin(), y = m.rows.begin();
	for (z = ans.rows.begin(); z != ans.rows.end(); ++z, ++x, ++y) {
		typename std::vector<T>::iterator zz = z->begin();
		typename std::vector<T>::const_iterator xx = x->begin(), yy = y->begin();
		while (zz != z->end()) {
			*zz++ = *xx++ + *yy++;
		}
	}
	return ans;
}*/
/*  This should print (to s) a "[ ", followed by each row of the matrix
    (using IntArray's << operator). These rows should be separated by
    ",\n". After the last row, you should print " ]" and return s.*/
template <typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if(rhs.getRows()==0){
    s<<"[  ]";
    return s;
  } 
  s<<"[ ";
  int i=0;
  for(i=0;i<rhs.getRows()-1;i++){
    s<<"{";
    int j=0;
    for(j=0;j<rhs.getColumns()-1;j++){
      s<<(rhs[i])[j]<<", ";  
    }
    s<<(rhs[i])[j]<<"},"<<std::endl;  
  }
  int j=0;
  s<<"{";
  for(j=0;j<rhs.getColumns()-1;j++){
    s<<(rhs[i])[j]<<", ";  
  }
  s<<(rhs[i])[j]<<"}"<<" ]";
  return s;
}

#endif
