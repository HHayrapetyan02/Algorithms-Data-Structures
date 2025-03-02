#include <iostream>
#include <vector>

using Pair = std::pair<int, int>;

Pair Union(const Pair& q1, const Pair& q2) {
  if (q1.first != q2.first) {
    return q1.first > q2.first ? q1 : q2;
  }
  return {q1.first, q1.second + q2.second};
}

class SegmentTree {
  int n_ = 0;
  std::vector<Pair> tree_;

 public:
  SegmentTree(std::vector<int>&, int& n);
  bool IsLeftSon(int);
  bool IsRightSon(int);
  Pair Max(int, int);
};

SegmentTree::SegmentTree(std::vector<int>& a, int& n) {
  n_ = n;
  tree_.resize(4 * n);
  for (int i = n; i < 2 * n; ++i) {
    tree_[i] = {a[i - n], 1};
  }
  for (int i = n - 1; i > 0; --i) {
    tree_[i] = Union(tree_[2 * i], tree_[2 * i + 1]);
  }
}

bool SegmentTree::IsLeftSon(int i) {
  return i % 2 == 1;
}

bool SegmentTree::IsRightSon(int i) {
  return i % 2 == 0;
}

Pair SegmentTree::Max(int l, int r) {
  Pair p = {0, 0};
  for (int i = l; i <= r; i /= 2, r /= 2) {
    if (IsLeftSon(i)) {
      if (p.first < tree_[i].first) {
        p = tree_[i];
      } else if (p.first == tree_[i].first) {
        p.second += tree_[i].second;
      }
      ++i;
    }
    if (IsRightSon(r)) {
      if (p.first < tree_[r].first) {
        p = tree_[r];
      } else if (p.first == tree_[r].first) {
        p.second += tree_[r].second;
      }
      --r;
    }
  }
  return p;
}

int main() {
  int n = 0;
  int k = 0;
  std::cin >> n;
  int pow = 1 << (32 - __builtin_clz(n));
  std::vector<int> arr(pow, 0);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  SegmentTree tree(arr, pow);
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    Pair q = {0, 0};
    std::cin >> q.first >> q.second;
    q = tree.Max(pow + q.first - 1, pow + q.second - 1);
    std::cout << q.first << " " << q.second << "\n";
  }
  return 0;
}
