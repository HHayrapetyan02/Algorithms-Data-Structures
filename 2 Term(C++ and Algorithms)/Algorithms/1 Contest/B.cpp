#include <iostream>
#include <cmath>
#include <iomanip>

struct Point {
  Point() = default;
  Point(double x, double y) : x(x), y(y) {
  }
  double x = 0;
  double y = 0;
};

struct Vector {
  Vector() = default;
  Vector(const int& x, const int& y) : x(x), y(y) {
  }
  int x = 0;
  int y = 0;
};

struct Line {
  Line() = default;
  Line(const int& x, const int& y, const int& c) : direct(x, y), c(c) {
  }
  Vector direct;
  int c = 0;
};

double LenVector(const Vector& vec) {
  return sqrt(vec.x * vec.x + vec.y * vec.y);
}

int LenVectorProduct(const Vector& first, const Vector& second) {
  return first.x * second.y - first.y * second.x;
}

bool ParallelLines(const Line& first, const Line& second) {
  return LenVectorProduct(first.direct, second.direct) == 0;
}

double LenDirection(const Line& line) {
  return LenVector(line.direct);
}

void DsitanceLines(const Line& first, const Line& second, double& len, Point& intersect) {
  if (ParallelLines(first, second)) {
    if (second.direct.x != 0) {
      len = std::abs(-first.c + second.c * first.direct.x / second.direct.x) / LenDirection(first);
    } else {
      len = std::abs(-first.c + second.c * first.direct.y / second.direct.y) / LenDirection(first);
    }
  } else {
    int ans = LenVectorProduct(first.direct, second.direct);
    intersect.x = 1.0 * (second.c * (-first.direct.x) + first.c * second.direct.x) / ans;
    intersect.y = 1.0 * (second.direct.y * first.c - second.c * first.direct.y) / ans;
  }
}

int main() {
  Line first;
  Line second;
  Point intersect;
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  std::cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
  first = {-b1, a1, c1};
  second = {-b2, a2, c2};
  double len = -1;
  DsitanceLines(first, second, len, intersect);
  std::cout << std::fixed << std::setprecision(6);
  std::cout << 1.0 * (-first.direct.x) << " " << 1.0 * (-first.direct.y) << "\n";
  std::cout << 1.0 * (-second.direct.x) << " " << 1.0 * (-second.direct.y) << "\n";
  if (len == -1) {
    std::cout << intersect.x << " " << intersect.y;
  } else {
    std::cout << len << "\n";
  }
  return 0;
}
