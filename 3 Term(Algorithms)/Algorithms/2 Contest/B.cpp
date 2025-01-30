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

void MaxGroup(std::vector<int64_t>& values) {
  auto size = static_cast<int64_t>(values.size());
  int64_t max = values[size - 1];
  int64_t diff = max - values[size - 2];
  int64_t left = size - 2;
  int64_t right = size - 1;
  int64_t right_tmp = size - 1;
  for (int64_t i = (size - 2); i >= 0; --i) {
    if (max - values[i] > diff) {
      left = i;
      right = right_tmp;
      diff = max - values[i];
    }
    if (values[i] > max) {
      max = values[i];
      right_tmp = i;
    }
  }
  std::cout << left + 1 << " " << right << " " << diff << "\n";
}

int main() {
  int64_t n = 0;
  std::cin >> n;
  std::vector<int64_t> values(n + 1, 0);
  std::cin >> values;
  PrefixSum(values);
  MaxGroup(values);
  return 0;
}
