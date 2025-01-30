#include <iostream>

int64_t Func(int n, int64_t** ans) {
  int64_t res = 0;

  for (int i = 0; i < 10; ++i) {
    ans[i][1] = 1;
  }

  for (int i = 0; i < 10; ++i) {
    if (i == 4 || i == 6) {
      ans[i][2] = 3;
      continue;
    }
    if (i == 5) {
      ans[i][2] = 0;
      continue;
    }
    ans[i][2] = 2;
  }

  for (int i = 3; i < n + 1; ++i) {
    ans[0][i] = ans[4][i - 1] + ans[6][i - 1];
    ans[1][i] = ans[6][i - 1] + ans[8][i - 1];
    ans[2][i] = ans[7][i - 1] + ans[9][i - 1];
    ans[3][i] = ans[4][i - 1] + ans[8][i - 1];
    ans[4][i] = ans[0][i - 1] + ans[3][i - 1] + ans[9][i - 1];
    ans[6][i] = ans[0][i - 1] + ans[1][i - 1] + ans[7][i - 1];
    ans[7][i] = ans[2][i - 1] + ans[6][i - 1];
    ans[8][i] = ans[1][i - 1] + ans[3][i - 1];
    ans[9][i] = ans[4][i - 1] + ans[2][i - 1];
  }

  for (int i = 1; i < 10; ++i) {
    if (i == 8) {
      continue;
    }
    res += ans[i][n];
  }

  return res;
}

int main() {
  int n = 0;
  std::cin >> n;

  auto ans = new int64_t*[10];
  for (int i = 0; i < 10; ++i) {
    ans[i] = new int64_t[n + 2]{};
  }

  std::cout << Func(n, ans) << "\n";

  for (int i = 0; i < 10; ++i) {
    delete[] ans[i];
  }
  delete[] ans;
  return 0;
}
