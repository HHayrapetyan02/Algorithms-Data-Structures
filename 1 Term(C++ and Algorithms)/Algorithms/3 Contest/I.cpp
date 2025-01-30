#include <iostream>
#include <cstring>

void Solution(char* a, char* b, size_t n, size_t m) {
  auto ans = new int*[n + 1];
  for (size_t i = 0; i < n + 1; ++i) {
    ans[i] = new int[m + 1]{};
  }

  for (size_t i = 0; i < n + 1; ++i) {
    ans[i][0] = static_cast<int>(i);
  }

  for (size_t j = 0; j < m + 1; ++j) {
    ans[0][j] = static_cast<int>(j);
  }

  for (size_t i = 1; i < n + 1; ++i) {
    for (size_t j = 1; j < m + 1; ++j) {
      if (a[i - 1] == b[j - 1]) {
        ans[i][j] = ans[i - 1][j - 1];
      } else {
        int res = std::min(ans[i - 1][j], ans[i][j - 1]);
        ans[i][j] = 1 + std::min(res, ans[i - 1][j - 1]);
      }
    }
  }

  std::cout << ans[n][m] << "\n";

  for (size_t i = 0; i < n + 1; ++i) {
    delete[] ans[i];
  }
  delete[] ans;
}

int main() {
  int const len = 5002;
  auto str_one = new char[len]{};
  auto str_two = new char[len]{};
  scanf("%s", str_one);
  scanf("%s", str_two);
  size_t n = std::strlen(str_one);
  size_t m = std::strlen(str_two);
  Solution(str_one, str_two, n, m);
  delete[] str_one;
  delete[] str_two;
  return 0;
}
