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

  double Length() const;
  Point Sum(Vector other);
  int32_t DotProduct(Vector other) const;
  int32_t CrossrProduct(Vector other) const;
  double AreaTriangle(Vector other) const;
  friend std::istream& operator>>(std::istream&, Vector&);
};

double Vector::Length() const {
  return sqrt(x * x + y * y);
}

Point Vector::Sum(Vector other) {
  int32_t x = this->x + other.x;
  int32_t y = this->y + other.y;
  return {x, y};
}

int32_t Vector::DotProduct(Vector other) const {
  return (this->x * other.x + this->y * other.y);
}

int32_t Vector::CrossrProduct(Vector other) const {
  return (this->x * other.y - this->y * other.x);
}

double Vector::AreaTriangle(Vector other) const {
  return fabs(1.0 * CrossrProduct(other) / 2);
}

std::istream& operator>>(std::istream& io, Vector& vector) {
  io >> vector.a.x >> vector.a.y >> vector.b.x >> vector.b.y;
  vector.x = vector.b.x - vector.a.x;
  vector.y = vector.b.y - vector.a.y;
  return io;
}

int main() {
  Vector first;
  Vector second;
  std::cin >> first >> second;

  std::cout << std::fixed << std::setprecision(6);
  Point sum = first.Sum(second);
  std::cout << first.Length() << " " << second.Length() << "\n";
  std::cout << 1.0 * sum.x << " " << 1.0 * sum.y << "\n";
  std::cout << 1.0 * first.DotProduct(second) << " " << 1.0 * first.CrossrProduct(second) << "\n";
  std::cout << 1.0 * first.AreaTriangle(second) << "\n";
  return 0;
}
