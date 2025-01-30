#include <iostream>

int64_t Func(int m, int n, int64_t** ans) {
  ans[0][0] = 1;
  for (int i = 0; i < n + 1; ++i) {
    for (int j = 0; j < m + 1; ++j) {
      if (i < n - 1 && j < m - 1) {
        ans[i + 1][j + 1] += ans[i][j];
      }
      if (i < n - 1) {
        ans[i + 1][j] += ans[i][j];
      }
      if (j < m - 1) {
        ans[i][j + 1] += ans[i][j];
      }
    }
  }

  return ans[n - 1][m - 1];
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> m >> n;
  auto ans = new int64_t*[n + 2];
  for (int i = 0; i < n + 2; ++i) {
    ans[i] = new int64_t[m + 2]{};
  }

  std::cout << Func(m, n, ans) << "\n";

  for (int i = 0; i < n + 2; ++i) {
    delete[] ans[i];
  }
  delete[] ans;
  return 0;
}
