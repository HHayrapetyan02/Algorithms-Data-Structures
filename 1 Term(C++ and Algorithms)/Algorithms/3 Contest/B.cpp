#include <iostream>

int64_t Solution(int n, int64_t* a) {
  a[1] = 3;
  a[2] = 8;
  for (int i = 3; i < n + 1; ++i) {
    a[i] = 2 * (a[i - 1] + a[i - 2]);
  }
  return a[n];
}

int main() {
  int n = 0;
  std::cin >> n;
  auto a = new int64_t[n + 2]{};
  std::cout << Solution(n, a) << "\n";
  delete[] a;
  return 0;
}
