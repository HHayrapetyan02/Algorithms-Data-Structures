#include <iostream>
#include <algorithm>

int Func(int n, int* arr, int* ans) {
  ans[0] = 99999;
  ans[1] = arr[1] - arr[0];
  if (n > 2) {
    ans[2] = arr[2] - arr[0];
  }

  for (int i = 3; i < n; ++i) {
    ans[i] = std::min(ans[i - 2] + arr[i] - arr[i - 1], ans[i - 3] + arr[i] - arr[i - 2]);
  }

  return ans[n - 1];
}

int main() {
  int n = 0;
  std::cin >> n;
  auto arr = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  auto b = new int[n]{};

  std::sort(arr, arr + n);
  std::cout << Func(n, arr, b) << "\n";

  delete[] arr;
  delete[] b;
  return 0;
}
