#include <iostream>
#include <string>
#include <vector>

void Prefix(const std::string& pattern, std::vector<int>& pref) {
  for (size_t i = 1; i < pattern.length(); ++i) {
    int k = pref[i - 1];
    while (pattern[i] != pattern[k] && k > 0) {
      k = pref[k - 1];
    }
    if (pattern[i] == pattern[k]) {
      pref[i] = k + 1;
    }
  }
}

void KMP(const std::string& string, const std::string& pattern, std::vector<int>& pref) {
  Prefix(pattern, pref);
  int last = 0;
  for (size_t i = 0; i < string.length(); ++i) {
    int k = last;
    while (k > 0 && (k == static_cast<int>(pattern.size()) || string[i] != pattern[k])) {
      k = pref[k - 1];
    }
    if (string[i] == pattern[k]) {
      ++k;
    }
    last = k;
    if (k == static_cast<int>(pattern.length())) {
      std::cout << i - static_cast<int>(pattern.length()) + 1 << "\n";
    }
  }
}

int main() {
  std::string string = " ";
  std::string pattern = " ";
  std::cin >> string >> pattern;
  std::vector<int> pref(pattern.length(), 0);
  KMP(string, pattern, pref);
  return 0;
}
