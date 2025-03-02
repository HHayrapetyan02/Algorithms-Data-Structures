#include <algorithm>
#include <iostream>
#include <vector>

int Parent(int n) {
  return (n - 1) / 2;
}

int Left(int n) {
  return 2 * n + 1;
}

int Right(int n) {
  return 2 * n + 2;
}

bool IsLeft(int n) {
  return (n % 2) == 1;
}

bool IsRight(int n) {
  return (n % 2) == 0;
}

class SegTree {
  std::vector<std::vector<int>> tree_;
  int size_x_;
  int size_y_;

 public:
  SegTree() = default;
  explicit SegTree(std::vector<std::vector<int>> &values, int n, int m) {
    int k = 1;
    while (k < n) {
      k *= 2;
    }
    values.resize(k);
    size_x_ = k;
    k = 1;
    while (k < m) {
      k *= 2;
    }
    for (int idx = 0; idx < size_x_; ++idx) {
      values[idx].resize(k, 0);
    }
    size_y_ = k;
    tree_ = std::vector<std::vector<int>>(2 * size_x_ - 1, std::vector<int>(2 * size_y_ - 1, 0));
    for (int i = size_x_ - 1; i < 2 * size_x_ - 1; ++i) {
      for (int j = size_y_ - 1; j < 2 * size_y_ - 1; ++j) {
        tree_[i][j] = values[i - size_x_ + 1][j - size_y_ + 1];
      }
    }
    for (int i = 2 * size_x_ - 2; i >= 0; --i) {
      for (int j = 2 * size_y_ - 2; j >= 0; --j) {
        if (Right(j) <= 2 * size_y_ - 1) {
          tree_[i][j] = std::min(tree_[i][Left(j)], tree_[i][Right(j)]);
        }
      }
    }
    for (int i = 2 * size_y_ - 2; i >= 0; --i) {
      for (int j = 2 * size_x_ - 2; j >= 0; --j) {
        if (Right(j) <= 2 * size_x_ - 1) {
          tree_[j][i] = std::min(tree_[Left(j)][i], tree_[Right(j)][i]);
        }
      }
    }
  }
  int64_t QueryX(int x, int l, int r, int node = 0, int a = 0, int b = 0) {
    if (node == 0) {
      b = size_y_ - 1;
    }
    if (a >= l && b <= r) {
      return tree_[x][node];
    }
    if ((a < l && b < l) || (a > r && b > r)) {
      return 10000000000;
    }
    int64_t l_res = QueryX(x, l, r, Left(node), a, (a + b) / 2);
    int64_t r_res = QueryX(x, l, r, Right(node), (a + b) / 2 + 1, b);
    int64_t ans = std::min(l_res, r_res);
    return ans;
  }
  int64_t Query(int l_x, int r_x, int l_y, int r_y, int node = 0, int a = 0, int b = 0) {
    if (node == 0) {
      b = size_x_ - 1;
    }
    if (a >= l_x && b <= r_x) {
      return QueryX(node, l_y, r_y);
    }
    if ((a < l_x && b < l_x) || (a > r_x && b > r_x)) {
      return 10000000000;
    }
    int64_t l_res = Query(l_x, r_x, l_y, r_y, Left(node), a, (a + b) / 2);
    int64_t r_res = Query(l_x, r_x, l_y, r_y, Right(node), (a + b) / 2 + 1, b);
    int64_t ans = std::min(l_res, r_res);
    return ans;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> values(n, std::vector<int>(m, 0));
  for (int idx = 0; idx < n; ++idx) {
    for (int j = 0; j < m; ++j) {
      std::cin >> values[idx][j];
    }
  }
  SegTree sol(values, n, m);
  int k = 0;
  std::cin >> k;
  for (int idx = 0; idx < k; ++idx) {
    int l_x = 0;
    int l_y = 0;
    int r_x = 0;
    int r_y = 0;
    std::cin >> l_x >> l_y >> r_x >> r_y;
    std::cout << sol.Query(l_x - 1, r_x - 1, l_y - 1, r_y - 1) << '\n';
  }
  return 0;
}
