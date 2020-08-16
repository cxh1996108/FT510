#include "function.hpp"
#include <exception>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
//next-README
int binarySearchForZero(Function<int, int> * f, int low, int high);

/*When you create an instance of CountedIntFn, you should pass in the
maximum number of invocations allowed, the actual function to compute
with, and a message which is useful to you to know what happened if
the test fails. */
class CountedIntFn : public Function<int,int> {
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;

public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): 
    remaining(n),
    f(fn),
    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
/*Your testing should include checking if the binary search
implementation invokes the f an appropriate number of times
(specifically, at most log2(high-low) + 1 times if high > low, and at
most once otherwise). */
/*in which I computed the maximum number of invocations of f, wrap f in
a CountedIntFn, perform the binary search, and check the answer. */
void check(Function<int,int> * f,int low,int high,int expected_ans,const char * mesg){
  int n;
  if(high < low){
    fprintf(stderr,"%s: high < low\n", mesg);
    exit(EXIT_FAILURE);
  }
  else if(high > low){
    n = log(high - low)/log(2) + 1;//logaB = log(B)/log(a)
  }
  else{
    n = 1;
  }
  CountedIntFn * function = new CountedIntFn(n, f, mesg);//IMPORTANT
  int ans = binarySearchForZero(function,low,high);
  //std::cout<<"ans="<<ans<<std::endl;
  //std::cout<<"expected_ans="<<expected_ans<<std::endl;
  if(ans != expected_ans){
    fprintf(stderr,"%s: Answer is wrong!\n", mesg);
    exit(EXIT_FAILURE);
  }
  delete function;
}
class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};
class NegativeFunction : public Function<int, int>
{
public:
  virtual int invoke(int arg) { 
    return -1; 
  }
};

class PositiveFunction : public Function<int, int>
{
public:
  virtual int invoke(int arg) { 
    return 2; 
  }
};
class LinearFunction : public Function<int, int>
{
public:
  virtual int invoke(int arg) { 
    return arg; 
  }
};
int main(int argc, char ** argv){
/*searching for its 0 in the range [0,150000), your function
should return 52359 in fewer than 20 invocations of f. */
  SinFunction f1;
  NegativeFunction nf;
  PositiveFunction pf;
  LinearFunction lf;
  check(&f1,0,150000,52359,"SinFunction");//add &
  check(&nf, 1, 5, 4, "Negative Function");
  check(&pf, 2, 10, 2, "Positive Function");
  check(&lf, -99999, 10000000, 0, "Linear Function");
  check(&lf, -99999999, -1000, -1001, "Negative linear Function");
  check(&lf, 2, 100000000, 2, "Positive linear Function");
  check(&lf, 0, 0, 0, "range");
  check(&lf, 10, 10, 10, "range");
  check(&lf, -1, 10000000, 0, "Linear Function");
  return EXIT_SUCCESS;
  
}