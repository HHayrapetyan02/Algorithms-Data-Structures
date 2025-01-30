#include <iostream>
#include <cmath>
#include <iomanip>

struct Point {
  Point() : x(0), y(0) {
  }
  Point(const int& x, const int& y) : x(x), y(y) {
  }
  int x = 0;
  int y = 0;
};

struct Vector {
  Vector() = default;
  Vector(const int& x, const int& y) : x(x), y(y) {
  }
  Vector(const Point& a, const Point& b) : x(b.x - a.x), y(b.y - a.y) {
  }
  int x = 0;
  int y = 0;
};

int64_t ScalarProduct(const Vector& first, const Vector& second) {
  return first.x * second.x + first.y * second.y;
}

int LenVectorProduct(const Vector& first, const Vector& second) {
  return first.x * second.y - first.y * second.x;
}

double LenVector(const Vector& vec) {
  return sqrt(vec.x * vec.x + vec.y * vec.y);
}

int64_t Direction(Point& a, Point& b, Point& c) {
  Vector ac(a, c);
  Vector ab(a, b);
  return LenVectorProduct(ac, ab);
}

bool OnSegment(Point& a, Point& b, Point& c) {
  Vector ac(a, c);
  Vector cb(c, b);
  return LenVectorProduct(ac, cb) == 0 && ScalarProduct(ac, cb) >= 0;
}

bool IntersectSegment(Point& a, Point& b, Point& c, Point& d) {
  int64_t d1 = Direction(c, d, a);
  int64_t d2 = Direction(c, d, b);
  int64_t d3 = Direction(a, b, c);
  int64_t d4 = Direction(a, b, d);
  bool flag = (d1 == 0) && (d2 == 0) && (d3 == 0) && (d4 == 0);
  if (flag) {
    return OnSegment(c, d, a) || OnSegment(c, d, b) || OnSegment(a, b, c) || OnSegment(a, b, d);
  }
  return (d1 * d2 <= 0 && d3 * d4 <= 0);
}

double Distance(Point& a, Point& b, Point& c) {
  Vector ab(a, b);
  Vector ac(a, c);
  Vector ba(b, a);
  Vector bc(b, c);
  double len = 0;
  if (ScalarProduct(ac, ab) <= 0) {
    len = LenVector(ac);
  } else if (ScalarProduct(bc, ba) <= 0) {
    len = LenVector(bc);
  } else {
    len = abs(LenVectorProduct(ac, ab)) / LenVector(ab);
  }
  return len;
}

double DistanceSegment(Point& a, Point& b, Point& c, Point& d) {
  double len = 0;
  if (IntersectSegment(a, b, c, d)) {
    len = 0;
  } else {
    double d1 = Distance(c, d, a);
    double d2 = Distance(c, d, b);
    double d3 = Distance(a, b, c);
    double d4 = Distance(a, b, d);
    double len1 = std::min(d1, d2);
    double len2 = std::min(d3, d4);
    len = std::min(len1, len2);
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
  Point d;
  std::cin >> a >> b >> c >> d;
  std::cout << std::fixed << std::setprecision(6);
  std::cout << DistanceSegment(a, b, c, d) << "\n";
  return 0;
}
