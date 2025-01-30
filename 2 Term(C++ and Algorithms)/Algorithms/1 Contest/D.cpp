#include <iostream>
#include <cmath>
#include <iomanip>

struct Point {
  int32_t x = 0;
  int32_t y = 0;
};

class Vector {
 public:
  Point a;
  Point b;
  int32_t x = 0;
  int32_t y = 0;

  Vector() = default;
  Vector(const Point&, const Point&);
  double Length() const;
  int32_t DotProduct(Vector other) const;
  int32_t CrossProduct(Vector other) const;
  double DistanceLine(Vector other);
  double DistanceRay(Vector other);
  double DistanceSegment(Vector, Point&, Point&, Point&);
  friend std::istream& operator>>(std::istream&, Vector&);
};

Vector::Vector(const Point& a, const Point& b) : x(b.x - a.x), y(b.y - a.y) {
}

double Vector::Length() const {
  return sqrt(x * x + y * y);
}

int32_t Vector::DotProduct(Vector other) const {
  return (this->x * other.x + this->y * other.y);
}

int32_t Vector::CrossProduct(Vector other) const {
  return (this->x * other.y - this->y * other.x);
}

double Vector::DistanceLine(Vector other) {
  return abs(CrossProduct(other)) / (other.Length());
}

double Vector::DistanceRay(Vector other) {
  double len = 0;
  if (DotProduct(other) > 0) {
    len = abs(CrossProduct(other)) / (other.Length());
  } else {
    len = Length();
  }
  return len;
}

double Vector::DistanceSegment(Vector other, Point& a, Point& b, Point& c) {
  Vector ab(a, b);
  Vector bc(b, c);
  Vector ba(b, a);
  double len = 0;
  if (ab.DotProduct(other) <= 0) {
    len = other.Length();
  } else if (bc.DotProduct(ba) <= 0) {
    len = bc.Length();
  } else {
    len = abs(other.CrossProduct(ab)) / (ab.Length());
  }
  return len;
}

std::istream& operator>>(std::istream& io, Point& a) {
  io >> a.x >> a.y;
  return io;
}

int main() {
  Point a;
  Point b;
  Point c;
  std::cin >> c >> a >> b;
  Vector ac(a, c);
  Vector ab(a, b);
  std::cout << std::fixed << std::setprecision(6);
  std::cout << ac.DistanceLine(ab) << "\n";
  std::cout << ac.DistanceRay(ab) << "\n";
  std::cout << ab.DistanceSegment(ac, a, b, c) << "\n";
  return 0;
}
