#include <iostream>

int64_t Func(int n, int64_t* arr) {
  arr[1] = 0;
  for (int i = 2; i < n + 1; ++i) {
    if (i % 6 == 0) {
      arr[i] = std::min(arr[i / 2], arr[i - 1]);
      arr[i] = std::min(arr[i], arr[i / 3]) + 1;
    } else if (i % 3 == 0) {
      arr[i] = std::min(arr[i / 3], arr[i - 1]) + 1;
    } else if (i % 2 == 0) {
      arr[i] = std::min(arr[i / 2], arr[i - 1]) + 1;
    } else {
      arr[i] = arr[i - 1] + 1;
    }
  }
  return arr[n];
}

int main() {
  int n = 0;
  std::cin >> n;
  auto arr = new int64_t[n + 1]{};
  std::cout << Func(n, arr) << "\n";
  delete[] arr;
  return 0;
}
