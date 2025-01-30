#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  int64_t height = 0;
  for (int i = 0; i < n; ++i) {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;
    height += std::max(a, b);
  }
  std::cout << height;
  return 0;
}
