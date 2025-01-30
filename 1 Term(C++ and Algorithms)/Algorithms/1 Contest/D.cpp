#include <iostream>

void Merge(int64_t* c, int64_t* a, int64_t n, int64_t* b, int64_t m) {
  int64_t i = 0;
  int64_t j = 0;
  int64_t k = 0;
  while ((i < n) && (j < m)) {
    if (a[i] <= b[j]) {
      c[k] = a[i];
      ++i;
    } else {
      c[k] = b[j];
      ++j;
    }
    ++k;
  }
  while (i < n) {
    c[k] = a[i];
    ++i;
    ++k;
  }
  while (j < m) {
    c[k] = b[j];
    ++j;
    ++k;
  }
}

void MergeSort(int64_t* arr, int64_t n) {
  if (n < 2) {
    return;
  }
  int64_t mid = n / 2;
  auto left = new int64_t[mid]{};
  auto right = new int64_t[n - mid]{};
  for (int64_t i = 0; i < mid; ++i) {
    left[i] = arr[i];
  }
  for (int64_t i = mid; i < n; ++i) {
    right[i - mid] = arr[i];
  }
  MergeSort(left, mid);
  MergeSort(right, n - mid);
  Merge(arr, left, mid, right, n - mid);
  delete[] left;
  delete[] right;
}

void Solution(int n, int64_t* arr, int sum) {
  int tmp_sum = 0;
  int max = arr[2] + arr[1];
  int j = 2;
  for (int i = 0; i < n - 1; ++i) {
    tmp_sum += arr[i];
    int res = arr[i] + arr[i + 1];
    int len = 2;
    int k = i + 2;
    while ((k < n) && (arr[k] + arr[k - 1] >= arr[i])) {
      res += arr[k];
      ++len;
      ++k;
    }
    if (res > max) {
      j = len;
      max = res;
    }
    if (sum - tmp_sum < max) {
      break;
    }
  }
  std::cout << j << " " << max;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  int sum = 0;
  std::cin >> n;
  auto arr = new int64_t[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
    sum += arr[i];
  }
  MergeSort(arr, n);
  auto arr_rev = new int64_t[n]{};
  for (int i = 0; i < n; i++) {
    arr_rev[i] = arr[n - 1 - i];
  }
  if (n == 1) {
    std::cout << 1 << " " << arr[0];
    delete[] arr;
    delete[] arr_rev;
    return 0;
  }
  if (n == 2) {
    std::cout << 2 << " " << arr[0] + arr[1];
    delete[] arr;
    delete[] arr_rev;
    return 0;
  }
  Solution(n, arr_rev, sum);
  delete[] arr;
  delete[] arr_rev;
  return 0;
}
