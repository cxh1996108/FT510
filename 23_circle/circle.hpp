#include "point.hpp"

class Circle{
  private:
    Point center;
    const double radius;//const should be in front of double
  public:
    Circle(Point p,const double r);
    void move (double dx, double dy);
    double intersectionArea(const Circle & otherCircle);
};