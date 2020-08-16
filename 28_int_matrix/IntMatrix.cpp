#include "IntMatrix.hpp"

/*  A default constructor: it should initialize the matrix to have 0
    rows and 0 columns.*/
IntMatrix::IntMatrix() : numRows(0), numColumns(0),rows(NULL) {
}
/*  A constructor that takes the number of rows and columns. It should
    initialize the matrix to have the specified number of rows and
    columns.*/
IntMatrix::IntMatrix(int r, int c) :numRows(r),numColumns(c),rows(new IntArray*[r]){
  for(int i=0;i<numRows;i++){
    rows[i] = new IntArray(numColumns);
  }
}
//  A copy constructor, which makes a deep copy.
IntMatrix::IntMatrix(const IntMatrix & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray*[numRows];
  for(int i=0;i<numRows;i++){
    rows[i] = new IntArray(numColumns);
    *rows[i] = *rhs.rows[i];//should I add *?
  }
}

//  A destructor, which frees any memory the Matrix has allocated.
IntMatrix::~IntMatrix() {
  for(int i=0;i<numRows;i++){
    delete rows[i];
  }
  delete[] rows;
}
//  An assignment operator, which makes a deep copy.
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if(this != &rhs){
 	  for (int i = 0; i < numRows; i++) {
		  delete rows[i];
	  }
	  delete[] rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    IntArray** temp = new IntArray*[rhs.numRows];
    for(int i=0;i<rhs.numRows;i++){
      temp[i] = new IntArray(numColumns);
      *temp[i] = *rhs.rows[i];//should I add *?
    }
    rows = temp;
  }
  return *this;
}
//THIS IS WRONG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if(this != &rhs){
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    IntArray** temp = new IntArray*[rhs.numRows];
    for(int i=0;i<rhs.numRows;i++){
      temp[i] = new IntArray(numColumns);
      *temp[i] = *rhs.rows[i];//should I add *?
      delete rows[i];
    }
    delete[] rows;
    rows = temp;
  }
  return *this;
}*/
//  Returns the number of rows.
int IntMatrix::getRows() const {
  return numRows;
}
//  Returns the number of columns.
int IntMatrix::getColumns() const {
  return numColumns;
}
/*  Uses assert() to check that index is valid and returns a reference
    to the requested row.*/
const IntArray & IntMatrix::operator[](int index) const {
  assert(index>=0);
  assert(index<numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index>=0);
  assert(index<numRows);
  return *rows[index];
}
/*  Compares two matrices for equality. The matrices are equal if they
    have the same number of rows, the same number of columns, and each
    element is the same as the corresponding element in the other
    matrix.*/
bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if(numRows!=rhs.numRows || numColumns!=rhs.numColumns){
    return false;
  }
  for(int i=0;i<numRows;i++){
    if(*rows[i]!=*rhs.rows[i]){ //Should I add *?
      return false;
    }
  }
  return true;
}
/*  Assert()s that this and rhs have the same dimensions and returns a
    matrix (also the same dimensions as this and rhs) whose elements
    are the sum of the corresponding elements of this matrix and rhs
    (does matrix addition). */
IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows);
  assert(numColumns == rhs.numColumns);
  IntMatrix s(numRows,numColumns);
  for(int i=0;i<numRows;i++){
    IntArray &z = *s.rows[i];
		IntArray &x = *rows[i];
		IntArray &y = *rhs.rows[i];
    for(int j=0;j<numColumns;j++){
      //(*s.rows[i])[j] = (*rows[i])[j]+(*rhs.rows[i])[j];//IMPORTANT
      z[j] = x[j] + y[j];
    }
  }
  return s;
}
/*  This should print (to s) a "[ ", followed by each row of the matrix
    (using IntArray's << operator). These rows should be separated by
    ",\n". After the last row, you should print " ]" and return s.*/
std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if(rhs.getRows()==0){
    s<<"[  ]";
    return s;
  } 
  s<<"[ ";
  int i=0;
  for(i=0;i<rhs.getRows()-1;i++){ 
    s<<rhs[i]<<",\n";
  }
  s<<rhs[i]<<" ]";
  return s;
}
