#include "circle.hpp"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
const double pi = 3.1415926;
Circle::Circle(Point p,const double r):center(p),radius(r){}

void Circle::move(double dx, double dy){
  center.move(dx,dy);
}

double Circle::intersectionArea(const Circle & otherCircle){
  double d = center.distanceFrom(otherCircle.center);
  double r1 = radius;
  double r2 = otherCircle.radius;
  if(d >= (r1 + r2)){
    return 0;
  }
  else if(d<=fabs(r1-r2) && d>=0) {
 	  if(r1>r2){
      return pi*r2*r2;}
    else{
      return pi*r1*r1;}
  }
  else{
    //The Law of Cosines
    double A1 = std::acos((d*d+r1*r1-r2*r2)/(2*d*r1)); 
    double A2 = std::acos((d*d+r2*r2-r1*r1)/(2*d*r2));
    double s1 = 0.5*r1*r1*std::sin(2*A1)+0.5*r2*r2*std::sin(2*A2);
    double s2 = A1*r1*r1+A2*r2*r2;//Circular sector
    double s = s2-s1;
    return s;
  }
}
/*Never mind, it turns out that the root path provided in README was wrong.

ln -s ../022_point/point.hpp => ln -s ../22_point/point.hpp

ln -s ../022_point/point.cpp => ln -s ../22_point/point.hpp*/