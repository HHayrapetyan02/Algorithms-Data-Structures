#include <iostream>
#include <vector>
#include <algorithm>

void ZFunction(std::vector<int>& string, std::vector<int32_t>& z) {
  z[0] = 0;
  int32_t left = 0;
  int32_t right = 0;
  for (int32_t i = 1; i < static_cast<int32_t>(string.size()); ++i) {
    if (i < right) {
      z[i] = std::min(z[i - left], right - i);
    }
    while (i + z[i] < static_cast<int32_t>(string.size()) && string[z[i]] == string[i + z[i]]) {
      ++z[i];
    }
    if (right < i + z[i]) {
      left = i;
      right = i + z[i];
    }
  }
}

void Mirror(std::vector<int32_t>& z, int32_t& n) {
  int32_t quantity = (n + 1) / 2;
  int32_t start = n % 2;
  while (start < n - 1) {
    if (z[n + start] >= quantity - start) {
      std::cout << quantity << " ";
    }
    ++quantity;
    start += 2;
  }
  std::cout << n << "\n";
}

std::istream& operator>>(std::istream& io, std::vector<int32_t>& vec) {
  for (size_t i = 0; i < vec.size() / 2; ++i) {
    io >> vec[i];
    vec[vec.size() - i - 1] = vec[i];
  }
  return io;
}

int main() {
  int32_t n = 0;
  int32_t m = 0;
  std::cin >> n >> m;
  std::vector<int32_t> str(2 * n, 0);
  std::cin >> str;
  std::vector<int32_t> z(2 * n, 0);
  ZFunction(str, z);
  Mirror(z, n);
  return 0;
}
