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
  int64_t x = 0;
  int64_t y = 0;
};

int64_t LenVectorProduct(const Vector& first, const Vector& second) {
  return first.x * second.y - first.y * second.x;
}

struct Polygon {
  int64_t size = 0;
  std::vector<Point> vertices;
};

long double Area(const Polygon& polygon) {
  int64_t area = 0;
  Point o(0, 0);
  for (int64_t i = 0; i < polygon.size - 1; ++i) {
    Vector first(o, polygon.vertices[i]);
    Vector second(o, polygon.vertices[i + 1]);
    area += LenVectorProduct(first, second);
  }
  Vector one(o, polygon.vertices[0]);
  Vector vec(o, polygon.vertices[polygon.size - 1]);
  area += LenVectorProduct(vec, one);
  auto ans = static_cast<long double>(area);
  return std::abs(ans) / 2;
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
  return io;
}

int main() {
  Polygon polygon;
  std::cin >> polygon;
  std::cout << std::fixed << std::setprecision(1);
  std::cout << Area(polygon) << "\n";
  return 0;
}
