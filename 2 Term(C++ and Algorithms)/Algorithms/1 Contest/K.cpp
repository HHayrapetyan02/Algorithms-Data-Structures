#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Point {
  int64_t x, y;
  friend std::istream& operator>>(std::istream& in, Point& p) {
    return in >> p.x >> p.y;
  }
  friend std::ostream& operator<<(std::ostream& out, const Point& p) {
    return out << p.x << ' ' << p.y << '\n';
  }
  explicit Point(const int64_t& x = 0, const int64_t& y = 0) : x(x), y(y) {
  }
};

class Vector {
  int64_t x_, y_;

 public:
  explicit Vector(const int64_t& x = 0, const int64_t& y = 0) : x_(x), y_(y) {
  }
  explicit Vector(const Point& p) : x_(p.x), y_(p.y) {
  }
  Vector(const Point& p1, const Point& p2) : x_(p2.x - p1.x), y_(p2.y - p1.y) {
  }
  int64_t& GetX() {
    return x_;
  }
  int64_t& GetY() {
    return y_;
  }
  const int64_t& GetX() const {
    return x_;
  }
  const int64_t& GetY() const {
    return y_;
  }
  friend int64_t DotProduct(const Vector& a, const Vector& b) {
    return a.x_ * b.x_ + a.y_ * b.y_;
  }
  friend int64_t CrossProduct(const Vector& a, const Vector& b) {
    return a.x_ * b.y_ - a.y_ * b.x_;
  }
  int64_t NormSquared() {
    return x_ * x_ + y_ * y_;
  }
  friend Vector operator+(const Vector& a, const Vector& b) {
    return Vector(a.x_ + b.x_, a.y_ + b.y_);
  }
  friend Vector operator-(const Vector& a, const Vector& b) {
    return Vector(a.x_ - b.x_, a.y_ - b.y_);
  }
  friend Vector operator*(const Vector& a, const int64_t& k) {
    return Vector(k * a.x_, k * a.y_);
  }
  friend Vector operator*(const int64_t& k, const Vector& a) {
    return Vector(k * a.x_, k * a.y_);
  }
  Vector operator+() {
    return Vector(x_, y_);
  }
  Vector operator-() {
    return Vector(-x_, -y_);
  }
  friend std::istream& operator>>(std::istream& in, Vector& a) {
    return in >> a.x_ >> a.y_;
  }
  friend std::ostream& operator<<(std::ostream& out, const Vector& a) {
    return out << a.x_ << ' ' << a.y_ << '\n';
  }
  friend Point operator+(const Point& p, const Vector& a) {
    return Point(p.x + a.x_, p.y + a.y_);
  }
  friend Point operator+(const Vector& a, const Point& p) {
    return Point(p.x + a.x_, p.y + a.y_);
  }
  friend Point operator-(const Point& p, const Vector& a) {
    return Point(p.x - a.x_, p.y - a.y_);
  }
};

struct Polygon {
  int64_t size;
  std::vector<Point> points;
};

std::istream& operator>>(std::istream& io, Polygon& polygon) {
  io >> polygon.size;
  for (int i = 0; i < polygon.size; ++i) {
    Point point;
    io >> point.x >> point.y;
    polygon.points.push_back(point);
  }
  return io;
}

std::vector<Point> ConvexHull(const Polygon& polygon) {
  if (polygon.size < 2) {
    return polygon.points;
  }
  std::vector<Point> vec(polygon.points);
  Point p0 = vec[0];
  for (const auto& p : vec) {
    if (p.x < p0.x || (p.x == p0.x && p.y < p0.y)) {
      p0 = p;
    }
  }
  std::sort(vec.begin(), vec.end(), [&p0](const Point& pa, const Point& pb) {
    Vector a(p0, pa);
    Vector b(p0, pb);
    int64_t angle = CrossProduct(a, b);
    return (angle ? angle < 0 : (a.NormSquared() < b.NormSquared()));
  });
  std::vector<Point> stack{vec[0], vec[1]};
  for (size_t i = 2; i < vec.size(); ++i) {
    Point p = vec[i];
    Point q = stack.back();
    Point r = stack[stack.size() - 2];
    while (CrossProduct(Vector(r, q), Vector(r, p)) >= 0) {
      stack.pop_back();
      if (stack.size() < 2) {
        break;
      }
      q = stack.back();
      r = stack[stack.size() - 2];
    }
    stack.push_back(p);
  }
  return stack;
}

long double Square(const std::vector<Point>& ans) {
  long double square = 0;
  for (size_t i = 1; i < ans.size() - 1; ++i) {
    Vector vec1(ans[0], ans[i]);
    Vector vec2(ans[0], ans[i + 1]);
    square += CrossProduct(vec1, vec2);
  }
  return square;
}

int main() {
  std::cout << std::fixed << std::setprecision(1);
  Polygon polygon;
  std::cin >> polygon;
  std::vector<Point> ans = ConvexHull(polygon);
  std::cout << ans.size() << '\n';
  for (const auto& p : ans) {
    std::cout << p;
  }
  std::cout << std::abs(Square(ans)) / 2;
}
