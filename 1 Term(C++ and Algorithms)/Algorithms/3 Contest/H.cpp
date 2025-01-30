#include <iostream>

void Func(int n, int* arr, int* ans) {
  auto prev = new int[n]{};

  for (int i = 0; i < n; ++i) {
    ans[i] = 1;
    prev[i] = -1;
    for (int j = 0; j < i; ++j) {
      if (arr[j] < arr[i]) {
        if (1 + ans[j] > ans[i]) {
          ans[i] = 1 + ans[j];
          prev[i] = j;
        }
      }
    }
  }

  int pos = 0;
  int res = ans[0];
  for (int i = 0; i < n; ++i) {
    if (ans[i] > res) {
      res = ans[i];
      pos = i;
    }
  }

  auto b = new int[n]{};
  int i = 0;
  for (i = 0; pos != -1; ++i) {
    b[i] = arr[pos];
    pos = prev[pos];
  }

  for (int j = i - 1; j >= 0; --j) {
    std::cout << b[j] << " ";
  }

  delete[] prev;
  delete[] b;
}

int main() {
  int n = 0;
  std::cin >> n;
  auto arr = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  auto ans = new int[n]{};

  Func(n, arr, ans);

  delete[] arr;
  delete[] ans;
  return 0;
}
