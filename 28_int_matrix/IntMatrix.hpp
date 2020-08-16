#ifndef __INT_MATRIX_HPP__
#define __INT_MATRIX_HPP__

#include <assert.h>

#include <iostream>

#include "IntArray.hpp"

class IntMatrix {
 private:
  int numRows;
  int numColumns;
  IntArray ** rows;

 public:
  IntMatrix();
  IntMatrix(int r, int c);
  IntMatrix(const IntMatrix & rhs);
  ~IntMatrix();
  IntMatrix & operator=(const IntMatrix & rhs);
  int getRows() const;
  int getColumns() const;
  const IntArray & operator[](int index) const;
  IntArray & operator[](int index);
  bool operator==(const IntMatrix & rhs) const;
  IntMatrix operator+(const IntMatrix & rhs) const;
};

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs);

#endif
