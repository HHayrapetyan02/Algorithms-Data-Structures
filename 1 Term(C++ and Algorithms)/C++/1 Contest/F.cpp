#include <iostream>
#include <cstring>

int main() {
  int k = 0;
  int n = 1000001;
  auto s = new char[n]{};
  int count = 0;
  std::cin >> k;
  char symbol = ' ';
  while (std::cin >> symbol) {
    s[count] = symbol;
    ++count;
  }
  count = 0;
  int64_t ans = 0;
  int tmp = 0;
  int len = strlen(s);
  while (count < len - k) {
    if (s[count] == s[count + k]) {
      ++tmp;
      ans += tmp;
      ++count;
    } else {
      tmp = 0;
      ++count;
    }
  }
  std::cout << ans;
  delete[] s;
  return 0;
}
