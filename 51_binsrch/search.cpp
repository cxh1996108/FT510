#include "function.hpp"
#include <cstdio>
#include <cstdlib>
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while(low +1 < high){//low < high is wrong, has to add 1
    int m = (low + high)/2;
    int t = f->invoke(m);
    if(t == 0){
      return m;
    }
    else if(t <= 0){
      low = m;
    }
    else{
      high = m;
    }
  }
  return low;
}