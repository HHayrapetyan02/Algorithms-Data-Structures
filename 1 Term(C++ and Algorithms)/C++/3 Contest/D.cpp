#include <iostream>

int BinarySearch(int64_t* a, int n, int64_t x) {
  int left = 0;
  int right = n;
  while (left < right) {
    int mid = (left + right) / 2;
    if (a[mid] < x) {
      left = mid + 1;
    } else if (a[mid] > x) {
      right = mid;
    } else {
      return mid;
    }
  }
  return -1;
}

int LowerBound(int64_t* a, int n, int64_t x) {
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

int UpperBound(int64_t* a, int n, int64_t x) {
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
  int m = 0;
  std::cin >> n;
  auto a = new int64_t[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::cin >> m;
  auto answer = new int64_t[m + 1]{};
  for (int j = 0; j < m; ++j) {
    int p = 0;
    std::cin >> p;
    int index = BinarySearch(a, n, p);
    if (index != -1) {
      answer[j] = UpperBound(a, n, a[index]) - LowerBound(a, n, a[index]) + 1;
    }
  }

  for (int k = 0; k < m; ++k) {
    std::cout << answer[k] << "\n";
  }

  delete[] a;
  delete[] answer;
  return 0;
}
