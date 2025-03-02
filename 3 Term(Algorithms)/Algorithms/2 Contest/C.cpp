#include <cmath>
#include <iostream>
#include <vector>

const auto kBit = 31;

class SparseTable {

  std::vector<std::vector<int32_t>> sparse_table_ = {};
  std::vector<size_t> pows_ = std::vector<size_t>(kBit + 1, 0);

 public:
  void BuildPows() {
    for (size_t i = 0; i <= kBit; ++i) {
      pows_[i] = 1 << i;
    }
  }

  SparseTable(const int &k, const std::vector<int32_t> &arr) {
    sparse_table_.resize(k + 1);
    for (size_t i = 1; i < arr.size(); ++i) {
      sparse_table_[0].emplace_back(arr[i]);
    }
    size_t num_iter = kBit - __builtin_clz(arr.size() - 1);
    for (size_t k = 1; k <= num_iter; ++k) {
      int32_t pow_k = 1 << (k - 1);
      for (size_t i = 0; i < sparse_table_[k - 1].size() - pow_k; ++i) {
        sparse_table_[k].emplace_back(std::min(sparse_table_[k - 1][i], sparse_table_[k - 1][i + pow_k]));
      }
    }
  }

  int32_t RMQ(const int32_t &l, const int32_t &r) {
    int32_t k = kBit - __builtin_clz(r - l + 1);
    return std::min(sparse_table_[k][l - 1], sparse_table_[k][r - this->pows_[k]]);
  }
};

std::istream &operator>>(std::istream &io, std::vector<int32_t> &vec) {
  for (size_t i = 1; i < vec.size(); ++i) {
    io >> vec[i];
  }
  return io;
}

int main() {
  int32_t n = 0;
  int32_t q = 0;
  std::cin >> n >> q;
  std::vector<int32_t> arr(n + 1, 0);
  std::cin >> arr;
  int32_t k = kBit - __builtin_clz(n);
  SparseTable sparse_table(k, arr);
  sparse_table.BuildPows();
  for (int32_t i = 0; i < q; ++i) {
    int32_t left = 0;
    int32_t right = 0;
    std::cin >> left >> right;
    std::cout << sparse_table.RMQ(left, right) << '\n';
  }
  return 0;
}
