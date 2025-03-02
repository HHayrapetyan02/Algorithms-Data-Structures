#include <iostream>
#include <vector>

struct Query {
  Query() : s(' '), l(0), r(0) {
  }
  Query(const char& s, const int& l, const int& r) : s(s), l(l), r(r) {
  }
  char s = ' ';
  int l = 0;
  int r = 0;
};

class FenwickTree {

  std::vector<int64_t> tree_;
  void BuildFenwickTree(std::vector<int64_t>&);

 public:
  explicit FenwickTree(std::vector<int64_t>& arr) {
    BuildFenwickTree(arr);
  }
  void Update(int64_t, int64_t);
  int64_t Query(int);
  int64_t Sum(int, int);
};

void FenwickTree::BuildFenwickTree(std::vector<int64_t>& a) {
  tree_.resize(a.size());
  for (size_t i = 0; i < a.size(); ++i) {
    int64_t x = 0;
    int64_t y = static_cast<int64_t>((i & (i + 1))) - 1;
    if (y >= 0) {
      x = a[(i & (i + 1)) - 1];
    }
    tree_[i] = a[i] - x;
  }
}

void FenwickTree::Update(int64_t index, int64_t delta) {
  for (size_t i = index; i < tree_.size(); i = i | (i + 1)) {
    tree_[i] += delta;
  }
}

int64_t FenwickTree::Query(int r) {
  int64_t sum = 0;
  for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
    sum += tree_[i];
  }
  return sum;
}

int64_t FenwickTree::Sum(int l, int r) {
  return Query(r) - Query(l - 1);
}

void PrefixSum(std::vector<int64_t>& arr, std::vector<int64_t>& prefix) {
  prefix[0] = arr[0];
  for (size_t i = 1; i < arr.size(); ++i) {
    prefix[i] = arr[i] + prefix[i - 1];
  }
}

std::istream& operator>>(std::istream& io, Query& q) {
  io >> q.s >> q.l >> q.r;
  return io;
}

std::istream& operator>>(std::istream& io, std::vector<int64_t>& vec) {
  for (size_t i = 0; i < vec.size(); ++i) {
    io >> vec[i];
  }
  return io;
}

int main() {
  int64_t n = 0;
  int64_t k = 0;
  std::cin >> n;
  std::vector<int64_t> values(n, 0);
  std::vector<int64_t> prefix(n, 0);
  std::cin >> values;
  std::cin >> k;
  PrefixSum(values, prefix);
  FenwickTree tree(prefix);
  for (int64_t i = 0; i < k; ++i) {
    Query q;
    std::cin >> q;
    if (q.s == 's') {
      std::cout << tree.Sum(q.l - 1, q.r - 1) << " ";
    } else {
      tree.Update(q.l - 1, -values[q.l - 1]);
      tree.Update(q.l - 1, q.r);
      values[q.l - 1] = q.r;
    }
  }
  return 0;
}
