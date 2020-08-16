/*The Point class must have the following public functionality:

  - A default constructor, which initializes the point's x and y to
    0. 

  - The method
      void move(double dx, double dy);
    which increases the point's x by dx, and its y by dy.

  - The method
      double distanceFrom(const Point & p);
    which takes a constant reference to another point and computes the
    distance between the two points. If you do not remember the
    formula for the distance between two points, you should be able to
    find this domain knowledge easily on the internet.*/
class Point{
private:
  double x;
  double y;
public:
  //default constructor
  Point();
  //method
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};