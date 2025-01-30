#include <iostream>

void Func(int** arr, int n, int t) {
  auto b = new int*[n];
  for (int i = 0; i < n; ++i) {
    b[i] = new int[n]{};
  }
  for (int p = 0; p < t; ++p) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int count = 0;
        if (i >= 1 && j >= 1 && arr[i - 1][j - 1] == 1) {
          ++count;
        }
        if (i >= 1 && arr[i - 1][j] == 1) {
          ++count;
        }
        if (i >= 1 && j <= n - 2 && arr[i - 1][j + 1] == 1) {
          ++count;
        }
        if (j >= 1 && arr[i][j - 1] == 1) {
          ++count;
        }
        if (j <= n - 2 && arr[i][j + 1] == 1) {
          ++count;
        }
        if (i <= n - 2 && j >= 1 && arr[i + 1][j - 1] == 1) {
          ++count;
        }
        if (i <= n - 2 && arr[i + 1][j] == 1) {
          ++count;
        }
        if (i <= n - 2 && j <= n - 2 && arr[i + 1][j + 1] == 1) {
          ++count;
        }

        if (count < 2 || count > 3) {
          b[i][j] = 0;
        } else if (count == 3) {
          b[i][j] = 1;
        } else {
          b[i][j] = arr[i][j];
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        arr[i][j] = b[i][j];
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    delete[] b[i];
  }
  delete[] b;
}

int main() {
  int n;
  int t;
  std::cin >> n >> t;
  auto arr = new int*[n];
  for (int i = 0; i < n; ++i) {
    arr[i] = new int[n]{};
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> arr[i][j];
    }
  }

  Func(arr, n, t);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << arr[i][j] << ' ';
    }
    std::cout << '\n';
  }

  for (int i = 0; i < n; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
  std::cin.get();
  return 0;
}
