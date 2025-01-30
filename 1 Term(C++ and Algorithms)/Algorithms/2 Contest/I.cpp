#include <iostream>
#include <algorithm>

int64_t Solution(int64_t* a, int64_t k, int64_t n) {
  int64_t b[2000001]{};
  int64_t cnt = 0;
  int64_t res = 0;
  for (int64_t i = 0; i < n;) {
    int64_t cnt = 0;
    while ((i + 1 < n) && (a[i] == a[i + 1])) {
      ++cnt;
      ++i;
    }
    ++cnt;
    ++i;
    b[res] = a[i - 1];
    b[res + 1] = cnt;
    res += 2;
  }
  for (int64_t j = 1; j < res; j += 2) {
    if (b[j] >= 3) {
      ++cnt;
    }
  }
  int64_t j = 0;
  for (int64_t i = 0; i < res / 2; ++i) {
    while ((j < i) && (b[j * 2] * k < b[i * 2])) {
      ++j;
    }
    cnt += 3 * (i - j) * (i - j - 1);
  }
  j = 0;
  for (int64_t i = 1; i < res / 2; ++i) {
    while ((2 * i < res) && (2 * j < res) && (j < i) && (b[j * 2] * k < b[i * 2])) {
      ++j;
    }
    if ((2 * i + 1 < res) && (b[2 * i + 1] > 1)) {
      cnt += 3 * (i - j);
    }
  }
  j = res / 2 - 1;
  for (int64_t i = res / 2 - 2; i >= 0; --i) {
    while ((2 * i < res) && (2 * j < res) && (j > i) && (b[j * 2] > b[i * 2] * k)) {
      --j;
    }
    if ((2 * i + 1 < res) && (b[2 * i + 1] > 1)) {
      cnt += 3 * (j - i);
    }
  }
  return cnt;
}

int main() {
  int64_t n = 0;
  int64_t k = 0;
  std::cin >> n >> k;
  auto arr = new int64_t[n]{};
  for (int64_t i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  std::sort(arr, arr + n);
  std::cout << Solution(arr, k, n);
  delete[] arr;
  return 0;
}
