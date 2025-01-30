#include <iostream>
#include <algorithm>

int LowerBound(int* a, int n, int x) {
  int left = 0;
  int right = n;
  while (left < right) {
    int mid = (left + right) / 2;
    if (a[mid] >= x) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}

int UpperBound(int* a, int n, int x) {
  int left = 0;
  int right = n;
  while (left < right) {
    int mid = (left + right) / 2;
    if (a[mid] <= x) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left - 1;
}

int main() {
  int n = 0;
  int x = 0;
  std::cin >> n;
  auto arr = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  std::cin >> x;

  std::sort(arr, arr + n);
  int len = LowerBound(arr, n, x);
  int index = UpperBound(arr, n, x);

  std::cout << index - len + 1 << "\n";

  delete[] arr;
  return 0;
}
