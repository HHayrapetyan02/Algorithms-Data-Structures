#include <iostream>

void HanoiTowers(int n, int x, int y) {
  if (n == 1) {
    std::cout << 1 << ' ' << x << ' ' << y << '\n';
  } else {
    HanoiTowers(n - 1, x, 6 - x - y);
    std::cout << n << ' ' << x << ' ' << y << '\n';
    HanoiTowers(n - 1, 6 - x - y, y);
  }
}

int main() {
  int n;
  std::cin >> n;
  HanoiTowers(n, 1, 3);
  return 0;
}
