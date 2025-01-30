#include <iostream>
#include <cstring>

const int32_t kLength = 10002;

void BiggestCommonSubseq(size_t n, char* a, size_t m, char* b) {
  size_t len = n;
  auto common_subseq = new int32_t*[n + 1];
  for (size_t i = 0; i < n + 1; ++i) {
    common_subseq[i] = new int32_t[m + 1]{};
  }

  for (size_t i = 1; i < n + 1; ++i) {
    for (size_t j = 1; j < m + 1; ++j) {
      if (a[i - 1] == b[j - 1]) {
        common_subseq[i][j] = common_subseq[i - 1][j - 1] + 1;
      } else {
        common_subseq[i][j] = std::max(common_subseq[i - 1][j], common_subseq[i][j - 1]);
      }
    }
  }

  size_t res = 0;
  while (n > 0 && m > 0) {
    if (a[n - 1] == b[m - 1]) {
      --n;
      --m;
      ++res;
    } else if (common_subseq[n - 1][m] == common_subseq[n][m]) {
      --n;
    } else {
      --m;
    }
  }
  std::cout << len - res << "\n";

  for (size_t i = 0; i < len + 1; ++i) {
    delete[] common_subseq[i];
  }
  delete[] common_subseq;
}

void CountPaloindrom(char* str) {
  size_t len = std::strlen(str);
  auto rev_str = new char[len + 1]{};
  for (size_t i = 0; i < len; ++i) {
    rev_str[i] = str[len - i - 1];
  }
  BiggestCommonSubseq(len, str, len, rev_str);
  delete[] rev_str;
}

int main() {
  auto str = new char[kLength]{};
  scanf("%s", str);
  CountPaloindrom(str);
  delete[] str;
  return 0;
}
