#include "point.hpp"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
Point::Point():x(0),y(0){}//default constructor

//increases the point's x by dx, and its y by dy.
void Point::move(double dx, double dy){
  x = x + dx;
  y = y + dy;
}
double Point::distanceFrom(const Point & p){
  double d;
  d = std::sqrt((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));//^ is wrong
  return d;
}

