#include <iostream>

int64_t Func(int64_t w, int64_t h, int64_t n) {
  int64_t min = 1;
  int64_t max = 0;
  if (w > h) {
    max = w * n;
  } else {
    max = h * n;
  }
  while (max - min > 1) {
    int64_t k = min + (max - min) / 2;
    if ((k / h) * (k / w) >= n) {
      max = k;
    } else {
      min = k;
    }
  }
  return max;
}

int main() {
  int64_t w = 0;
  int64_t h = 0;
  int64_t n = 0;
  std::cin >> w >> h >> n;
  std::cout << Func(w, h, n) << "\n";
  return 0;
}
