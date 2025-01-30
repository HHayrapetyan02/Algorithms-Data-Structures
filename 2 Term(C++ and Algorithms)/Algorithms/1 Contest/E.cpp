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
  Vector(const Point&, const Point&);
  double Length() const;
  int32_t DotProduct(Vector) const;
  int32_t CrossProduct(Vector) const;
  int64_t Direction(Vector);
  bool OnSegment(Vector);
  bool IntersectSegment(Vector, Point&, Point&, Point&, Point&);
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

int64_t Vector::Direction(Vector other) {
  return CrossProduct(other);
}

bool Vector::OnSegment(Vector other) {
  return CrossProduct(other) == 0 && DotProduct(other) >= 0;
}

bool Vector::IntersectSegment(Vector other, Point& a, Point& b, Point& c, Point& d) {
  Vector cd(c, d);
  Vector cb(c, b);
  Vector ac(a, c);
  Vector ab(a, b);
  Vector ad(a, d);
  Vector bd(b, d);
  Vector db(d, b);

  int64_t d1 = other.Direction(cd);
  int64_t d2 = cb.Direction(cd);
  int64_t d3 = ac.Direction(ab);
  int64_t d4 = ad.Direction(ab);
  bool flag = (d1 == 0) && (d2 == 0) && (d3 == 0) && (d4 == 0);
  if (flag) {
    return other.OnSegment(ad) || cb.OnSegment(bd) || ac.OnSegment(cb) || ad.OnSegment(db);
  }
  return (d1 * d2 <= 0 && d3 * d4 <= 0);
}

std::istream& operator>>(std::istream& io, Point& a) {
  io >> a.x >> a.y;
  return io;
}

int main() {
  Point a;
  Point b;
  Point c;
  Point d;
  std::cin >> a >> b >> c >> d;
  Vector ab(a, b);
  Vector ca(c, a);
  if (ab.IntersectSegment(ca, a, b, c, d)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  return 0;
}
