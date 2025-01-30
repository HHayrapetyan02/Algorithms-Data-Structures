#include <iostream>

int64_t Fib(int n, int64_t* array) {
  array[1] = 2;
  array[2] = 3;
  for (int i = 3; i < n + 1; ++i) {
    array[i] = array[i - 1] + array[i - 2];
  }
  return array[n];
}

int main() {
  int n = 0;
  std::cin >> n;
  auto array = new int64_t[n + 1]{};
  std::cout << Fib(n, array) << "\n";
  delete[] array;
  return 0;
}
