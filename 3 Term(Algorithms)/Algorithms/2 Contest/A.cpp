#include <iostream>
#include <vector>

void PrefixSum(std::vector<int64_t>& vec) {
  for (size_t i = 2; i < vec.size(); ++i) {
    vec[i] += vec[i - 1];
  }
}

std::istream& operator>>(std::istream& io, std::vector<int64_t>& vec) {
  for (size_t i = 1; i < vec.size(); ++i) {
    io >> vec[i];
  }
  return io;
}

std::istream& operator>>(std::istream& io, std::vector<std::pair<int64_t, int64_t>>& vec) {
  for (size_t i = 0; i < vec.size(); ++i) {
    int64_t left = 0;
    int64_t right = 0;
    io >> left >> right;
    vec[i] = {left, right};
  }
  return io;
}

int main() {
  int64_t n = 0;
  int64_t k = 0;
  std::cin >> n;
  std::vector<int64_t> values(n + 1, 0);
  std::cin >> values;
  std::cin >> k;
  std::vector<std::pair<int64_t, int64_t>> querys(k + 1);
  std::cin >> querys;
  PrefixSum(values);
  for (int64_t i = 0; i < k; ++i) {
    std::cout << values[querys[i].second] - values[querys[i].first - 1] << " ";
  }
  return 0;
}
