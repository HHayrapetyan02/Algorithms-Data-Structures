#include <iostream>

void Merge(int64_t *a, int64_t *b, int64_t n, int64_t *c, int64_t m) {
  int64_t i = 0;
  int64_t j = 0;
  int64_t k = 0;
  while ((i < n) && (j < m)) {
    if (b[i] <= c[j]) {
      a[k] = b[i];
      ++i;
    } else {
      a[k] = c[j];
      ++j;
    }
    ++k;
  }
  while (i < n) {
    a[k] = b[i];
    ++i;
    ++k;
  }
  while (j < m) {
    a[k] = c[j];
    ++j;
    ++k;
  }
}

void MergeSort(int64_t *arr, int64_t n) {
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

int Check(int mid, int n, int m, int k, int64_t *arr) {
  int s = 0;
  int j = 0;
  for (int i = 0; i < n - k + 1; ++i) {
    --j;
    if (j < 1 && arr[i] <= mid) {
      ++s;
      j = k;
    }
  }
  if (s >= m) {
    return 1;
  }
  return 0;
}

int Solution(int n, int m, int k, int64_t *a) {
  auto b = new int64_t[n - k + 1]{};
  for (int i = 0; i < n - k + 1; ++i) {
    b[i] = a[i + k - 1] - a[i];
  }
  int left = -1;
  int right = a[n - 1] - a[0];
  int mid;
  int check;
  if (m > 1) {
    while (left != right - 1) {
      mid = (left + right) / 2;
      check = Check(mid, n, m, k, b);
      if (check == 1) {
        right = mid;
      } else {
        left = mid;
      }
    }
    delete[] b;
    return right;
  }
  int min = 100000000;
  for (int i = 0; i < n - k + 1; ++i) {
    if (b[i] < min) {
      min = b[i];
    }
  }
  delete[] b;
  return min;
}

int main() {
  int n;
  int m;
  int k;
  std::cin >> n >> m >> k;
  auto arr = new int64_t[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  MergeSort(arr, n);
  std::cout << Solution(n, m, k, arr);
  delete[] arr;
  return 0;
}
