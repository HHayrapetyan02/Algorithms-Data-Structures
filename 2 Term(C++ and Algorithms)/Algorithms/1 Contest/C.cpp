#include <iostream>
#include <cmath>

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
  Vector(const int32_t&, const int32_t&);
  Vector(const Point&, const Point&);
  double Length() const;
  int32_t DotProduct(Vector other) const;
  int32_t CrossrProduct(Vector other) const;
  bool IntersectLine(Vector other) const;
  bool IntersectRay(Vector other) const;
  bool IntersectSegment(Vector other, Point&, Point&, Point&) const;
  friend std::istream& operator>>(std::istream&, Vector&);
};

Vector::Vector(const int32_t& x, const int32_t& y) : x(x), y(y) {
}

Vector::Vector(const Point& a, const Point& b) : x(b.x - a.x), y(b.y - a.y) {
}

double Vector::Length() const {
  return sqrt(x * x + y * y);
}

int32_t Vector::DotProduct(Vector other) const {
  return (this->x * other.x + this->y * other.y);
}

int32_t Vector::CrossrProduct(Vector other) const {
  return (this->x * other.y - this->y * other.x);
}

bool Vector::IntersectLine(Vector other) const {
  return CrossrProduct(other) == 0;
}

bool Vector::IntersectRay(Vector other) const {
  return IntersectLine(other) && DotProduct(other) >= 0;
}

bool Vector::IntersectSegment(Vector other, Point& a, Point& b, Point& c) const {
  Vector ac(c.x - a.x, c.y - a.y);
  Vector cb(b.x - c.x, b.y - c.y);
  return IntersectLine(other) && ac.DotProduct(cb) >= 0;
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
  Vector cb(c, b);
  if (ac.IntersectLine(ab)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }

  if (ac.IntersectRay(ab)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }

  if (ac.IntersectSegment(cb, a, b, c)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  return 0;
}
