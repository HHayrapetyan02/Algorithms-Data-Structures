#include <iostream>

void BinarySearch(int* a, int n, int k) {
  int left = 0;
  int right = n;
  int middle = 0;
  while (right - left > 1) {
    middle = (right + left) / 2;
    if (a[middle] >= k) {
      right = middle;
    } else {
      left = middle;
    }
  }
  a[right] = k;
}

int Func(int n, int* arr, int* ans) {
  const int inf = 9999999;
  ans[0] = -inf;
  for (int i = 1; i < n; ++i) {
    ans[i] = inf;
  }

  for (int i = 0; i < n; ++i) {
    BinarySearch(ans, n, arr[i]);
  }

  int i = 0;
  for (i = 0; i < n + 1 && ans[i] != inf;) {
    ++i;
  }

  return i;
}

int main() {
  int n = 0;
  std::cin >> n;
  auto arr = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  auto ans = new int[n]{};

  std::cout << Func(n, arr, ans) - 1 << "\n";

  delete[] arr;
  delete[] ans;
  return 0;
}
