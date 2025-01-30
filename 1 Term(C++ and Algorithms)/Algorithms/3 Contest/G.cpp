#include <iostream>

void Func(int n, int* arr, int m, int* b) {
  int len = 1001;
  auto ans = new int*[len];
  for (int i = 0; i < len; ++i) {
    ans[i] = new int[len]{0};
  }

  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < m + 1; ++j) {
      if (arr[i - 1] == b[j - 1]) {
        ans[i][j] = 1 + ans[i - 1][j - 1];
      } else {
        ans[i][j] = std::max(ans[i - 1][j], ans[i][j - 1]);
      }
    }
  }

  auto res = new int[len]{};
  int i = 0;
  while (n > 0 && m > 0) {
    if (arr[n - 1] == b[m - 1]) {
      res[i] = arr[n - 1];
      --n;
      --m;
      ++i;
    } else if (ans[n - 1][m] == ans[n][m]) {
      --n;
    } else {
      --m;
    }
  }

  for (int k = i - 1; k >= 0; --k) {
    std::cout << res[k] << " ";
  }

  for (int i = 0; i < len; ++i) {
    delete[] ans[i];
  }
  delete[] ans;
  delete[] res;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n;
  auto arr = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  std::cin >> m;
  auto b = new int[m]{};
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }

  Func(n, arr, m, b);

  delete[] arr;
  delete[] b;
  return 0;
}
