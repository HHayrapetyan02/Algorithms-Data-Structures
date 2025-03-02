#include <iostream>
#include <vector>

int GCD(int first, int second) {
  while (first != 0 && second != 0) {
    if (first > second) {
      first %= second;
    } else {
      second %= first;
    }
  }
  if (first == 0) {
    return second;
  }
  return first;
}

class SegmentTree {
  int n_ = 0;
  std::vector<int> tree_;

 public:
  SegmentTree(std::vector<int>&, int&);
  bool IsLeftSon(int);
  bool IsRightSon(int);
  int Query(int, int);
};

SegmentTree::SegmentTree(std::vector<int>& a, int& n) {
  n_ = n;
  tree_.resize(4 * n);
  for (int i = n; i < 2 * n; ++i) {
    tree_[i] = a[i - n];
  }
  for (int i = n - 1; i > 0; --i) {
    tree_[i] = GCD(tree_[2 * i], tree_[2 * i + 1]);
  }
}

bool SegmentTree::IsLeftSon(int i) {
  return i % 2 == 1;
}

bool SegmentTree::IsRightSon(int i) {
  return i % 2 == 0;
}

int SegmentTree::Query(int l, int r) {
  int res = tree_[l];
  for (int i = l; i <= r; i /= 2, r /= 2) {
    if (IsLeftSon(i)) {
      res = GCD(res, tree_[i]);
      ++i;
    }
    if (IsRightSon(r)) {
      res = GCD(res, tree_[r]);
      --r;
    }
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int k = 0;
  std::cin >> n;
  int pow = 1 << (32 - __builtin_clz(n));
  std::vector<int> arr(pow, 0);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  for (int i = n; i < pow; ++i) {
    arr[i] = arr[n - 1];
  }
  SegmentTree tree(arr, pow);
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int l = 0;
    int r = 0;
    std::cin >> l >> r;
    std::cout << tree.Query(pow + l - 1, pow + r - 1) << "\n";
  }
  return 0;
}
