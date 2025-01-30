#include <iostream>
#include <vector>

using Vector = std::vector<std::vector<std::vector<int>>>;
using Vec2 = std::vector<std::vector<int>>;
using Vec1 = std::vector<int>;

struct Point {
  int x = 0;
  int y = 0;
  int z = 0;
  int m = 0;
  Point() : x(0), y(0), z(0), m(0) {
  }
  Point(const int& x, const int& y, const int& z, const int& m) : x(x), y(y), z(z), m(m) {
  }
};

class Fenwick3D {
  int n_ = 0;
  Vector tree_;

 public:
  explicit Fenwick3D(int);
  void Update(const Point&);
  int Query(const Point&);
  int Sum(const Point&, const Point&);
};

Fenwick3D::Fenwick3D(int n) : n_(n), tree_(n + 1, Vec2(n + 1, Vec1(n + 1, 0))) {
}

void Fenwick3D::Update(const Point& p) {
  for (int i = p.x; i < n_ + 1; i = (i | (i + 1))) {
    for (int j = p.y; j < n_ + 1; j = (j | (j + 1))) {
      for (int k = p.z; k < n_ + 1; k = (k | (k + 1))) {
        tree_[i][j][k] += p.m;
      }
    }
  }
}

int Fenwick3D::Query(const Point& p) {
  int sum = 0;
  for (int i = p.x; i >= 0; i = (i & (i + 1)) - 1) {
    for (int j = p.y; j >= 0; j = (j & (j + 1)) - 1) {
      for (int k = p.z; k >= 0; k = (k & (k + 1)) - 1) {
        sum += tree_[i][j][k];
      }
    }
  }
  return sum;
}

int Fenwick3D::Sum(const Point& p1, const Point& p2) {
  Point x2y2z1 = {p2.x, p2.y, p1.z - 1, 0};
  Point x1y2z2 = {p1.x - 1, p2.y, p2.z, 0};
  Point x1y2z1 = {p1.x - 1, p2.y, p1.z - 1, 0};
  Point x2y1z2 = {p2.x, p1.y - 1, p2.z, 0};
  Point x2y1z1 = {p2.x, p1.y - 1, p1.z - 1, 0};
  Point x1y1z2 = {p1.x - 1, p1.y - 1, p2.z, 0};
  Point x1y1z1 = {p1.x - 1, p1.y - 1, p1.z - 1, 0};
  return Query(p2) - Query(x2y2z1) - Query(x1y2z2) + Query(x1y2z1) - Query(x2y1z2) + Query(x2y1z1) - Query(x1y1z1) +
         Query(x1y1z2);
}

std::istream& operator>>(std::istream& io, Point& p) {
  io >> p.x >> p.y >> p.z;
  return io;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int q = 0;
  std::cin >> n;
  std::cin >> q;
  Fenwick3D tree(n);
  while (q != 3) {
    if (q == 1) {
      Point p;
      std::cin >> p >> p.m;
      tree.Update(p);
    } else if (q == 2) {
      Point p1;
      Point p2;
      std::cin >> p1 >> p2;
      std::cout << tree.Sum(p1, p2) << "\n";
    }
    std::cin >> q;
  }
  return 0;
}
