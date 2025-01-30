#include <iostream>

int F(int** arr, int n, int k) {
  static int res = 0;
  if (k == n) {
    ++res;
  } else {
    for (int i = 0; i < n; ++i) {
      if (arr[i][0] == 0) {
        auto new_arr = new int*[n];
        for (int i = 0; i < n; ++i) {
          new_arr[i] = new int[n - k];
        }
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n - k; ++j) {
            new_arr[i][j] = arr[i][j];
          }
        }
        int tmp1 = i - 1;
        int tmp2 = i + 1;
        for (int j = 1; j < n - k; ++j) {
          if (tmp1 >= 0) {
            new_arr[tmp1][j] = 1;
            --tmp1;
          }
          if (tmp2 <= n - 1) {
            new_arr[tmp2][j] = 1;
            ++tmp2;
          }
          new_arr[i][j] = 1;
        }
        auto new_arr1 = new int*[n];
        for (int i = 0; i < n; ++i) {
          new_arr1[i] = new int[n - k - 1];
        }
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n - k - 1; ++j) {
            new_arr1[i][j] = new_arr[i][j + 1];
          }
        }
        F(new_arr1, n, k + 1);
        for (int i = 0; i < n; ++i) {
          delete[] new_arr[i];
          delete[] new_arr1[i];
        }
        delete[] new_arr;
        delete[] new_arr1;
      }
    }
  }
  return res;
}

int main() {
  int n;
  std::cin >> n;
  auto arr = new int*[n];
  for (int i = 0; i < n; ++i) {
    arr[i] = new int[n]{};
  }
  std::cout << F(arr, n, 0);
  for (int i = 0; i < n; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
  std::cin.get();
  return 0;
}
