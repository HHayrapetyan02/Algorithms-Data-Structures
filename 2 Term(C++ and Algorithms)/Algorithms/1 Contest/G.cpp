#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

struct Point {
  Point() : x(0), y(0) {
  }
  Point(const int64_t& x, const int64_t& y) : x(x), y(y) {
  }
  int64_t x = 0;
  int64_t y = 0;
};

struct Vector {
  Vector() = default;
  Vector(const int64_t& x, const int64_t& y) : x(x), y(y) {
  }
  Vector(const Point& a, const Point& b) : x(b.x - a.x), y(b.y - a.y) {
  }
  double LenVector() const {
    return sqrt(static_cast<double>(x * x + y * y));
  }
  int64_t x = 0;
  int64_t y = 0;
};

int64_t LenVectorProduct(const Vector& first, const Vector& second) {
  int64_t ans = 0;
  int64_t res = first.x * second.y - first.y * second.x;
  if (res == 0) {
    ans = 0;
  } else if (res > 0) {
    ans = 1;
  } else {
    ans = -1;
  }
  return ans;
}

Vector operator-(const Point& a, const Point& b) {
  Vector tmp(b, a);
  return tmp;
}

struct Polygon {
  int64_t size = 0;
  std::vector<Point> vertices;
  std::vector<Vector> vectors;
};

bool IsConvex(const Polygon& polygon) {
  int64_t count = 0;
  while (LenVectorProduct(polygon.vectors[count], polygon.vectors[count + 1]) == 0) {
    ++count;
  }
  int64_t tmp = LenVectorProduct(polygon.vectors[count], polygon.vectors[count + 1]);
  for (int64_t i = count + 1; i < polygon.size - 1; ++i) {
    int64_t ans = LenVectorProduct(polygon.vectors[i], polygon.vectors[i + 1]);
    if (ans != 0 && ans != tmp) {
      return false;
    }
  }
  int64_t ans = LenVectorProduct(polygon.vectors[polygon.size - 1], polygon.vectors[0]);
  return (ans == 0 || ans == tmp);
}

std::istream& operator>>(std::istream& io, Point& point) {
  io >> point.x >> point.y;
  return io;
}

std::istream& operator>>(std::istream& io, Polygon& polygon) {
  io >> polygon.size;
  for (int64_t i = 0; i < polygon.size; ++i) {
    Point point;
    io >> point;
    polygon.vertices.push_back(point);
  }
  for (int64_t i = 0; i < polygon.size - 1; ++i) {
    polygon.vectors.push_back(polygon.vertices[i + 1] - polygon.vertices[i]);
  }
  Vector vec = polygon.vertices[0] - polygon.vertices[polygon.size - 1];
  polygon.vectors.push_back(vec);
  return io;
}

int main() {
  Polygon polygon;
  std::cin >> polygon;
  if (IsConvex(polygon)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  return 0;
}
