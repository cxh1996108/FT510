#include "IntArray.hpp"
#include <assert.h>
#include <ostream>

//  A default constructor, which initalizes the size to 0 and the array to NULL 
IntArray::IntArray():data(NULL),numElements(0) {
}
//  A constructor that takes an int, which initializes the size to the
//  int passed in and the array to hold that many ints 
IntArray::IntArray(int n):data(new int[n]),numElements(n) {
}
//  A copy constructor, which performs a deep copy
IntArray::IntArray(const IntArray & rhs):data(new int[rhs.numElements]),numElements(rhs.numElements) {
  for(int i=0;i<rhs.numElements;i++){
    data[i] = rhs.data[i];
  }
}
//  A destructor, which releases any allocated memory
IntArray::~IntArray() {
  delete[] data;
}
//  An assignment operator, which performs a deep copy
IntArray & IntArray::operator=(const IntArray & rhs) {
  if(this != &rhs){
    int* temp = new int[rhs.numElements];
    for(int i=0;i<rhs.numElements;i++){
      temp[i] = rhs.data[i];
    }
    delete[] data;
    numElements = rhs.numElements;
    data = temp;
  }
  return *this;
}
/*  An [] operator, which checks if the index is in bounds (use
    assert), then returns a reference to the appropriate element
    Note: there are two versions of this operator: 
      int & operator[](int index);
      const int & operator[](int index) const;
    They will have the exact same code. The difference is that if the
    object they are invoked on is "const", then the second will be
    used, returning a "const" reference, preventing modification of
    the object. */
const int & IntArray::operator[](int index) const {
  //assert(index<numElements);
  //assert(index>=0);
  assert(0 <= index && index < numElements);
  return data[index];//IMPORTANT
}
int & IntArray::operator[](int index) {
  //assert(index<numElements);
  //assert(index>=0);
  assert(0 <= index && index < numElements);
  return data[index];//IMPORTANT
}
//  A size function, which returns the size of the arrray
int IntArray::size() const {
  return numElements;
}
/*  An == operator, which checks two arrays to see if the have the
    same contents, i.e., they have the same number of elements, and
    each element is the same as the element in the other array at the
    same index*/
bool IntArray::operator==(const IntArray & rhs) const {
  if(rhs.numElements!=numElements){
    return false;
  }
  for(int i=0;i<numElements;i++){
    if(rhs.data[i]!=data[i]){
      return false;
    }
  }
  return true;
}
//  A != operator, which functions as the opposite of the == operator
bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);//IMPORTANT
}
//Add this function to solve 28
/*IntArray IntArray::operator+(const IntArray & rhs) const {
  assert(numElements == rhs.numElements);
  IntArray temp; 
  temp.data = new int[numElements];
  temp.numElements = numElements;
  for(int i=0;i<numElements;i++){
    temp.data[i] = data[i]+rhs.data[i];
  }
  return temp;
}*/
/*  The << operator should be overloaded on std::ostream and const
    IntArray & to print the array in this format:
    {element0, element1, element2, ... elementN-2, elementN-1}*/
std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  //numElements == 0?????
  //rhs.numElements is wrong    IMPORTANT!!!!!
  //error: ‘int IntArray::numElements’ is private within this context
  s<<'{';
  if(rhs.size() == 0){//testcase1
    s<<'}';
    return s;
  }
  if(rhs.size() == 1){
    s<<rhs[0]<<'}';
    return s;
  }
  int i=0;
  for(i=0;i<rhs.size()-1;i++){ 
    s<<rhs[i];
    s<<',';
  }
  s<<rhs[i]<<'}';
  return s;
}


