#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n;
  std::vector<int64_t> colors(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> colors[i];
  }
  std::cin >> m;
  std::pair<std::vector<int64_t>::iterator, std::vector<int64_t>::iterator> p;
  for (int i = 0; i < m; ++i) {
    int64_t color = 0;
    std::cin >> color;
    p = std::equal_range(colors.begin(), colors.end(), color);
    std::cout << p.second - p.first << "\n";
  }
  return 0;
}
