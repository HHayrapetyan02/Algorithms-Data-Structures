#include <iostream>
#include <string>
#include <vector>

void Prefix(std::string& string, std::vector<int32_t>& pref) {
  for (size_t i = 1; i < string.length(); ++i) {
    int32_t k = pref[i - 1];
    while (string[i] != string[k] && k > 0) {
      k = pref[k - 1];
    }
    if (string[i] == string[k]) {
      pref[i] = k + 1;
    }
  }
}

int32_t KMP(std::string& string, std::string& pattern, std::vector<int32_t>& pref) {
  int32_t last = 0;
  int32_t diff = static_cast<int32_t>(string.length()) - static_cast<int32_t>(pattern.length());
  int32_t start = diff > 0 ? diff : 0;
  for (int32_t i = start; i < static_cast<int32_t>(string.length()); ++i) {
    int32_t k = last;
    while (k > 0 && (k == static_cast<int32_t>(pattern.length()) || string[i] != pattern[k])) {
      k = pref[k - 1];
    }
    if (string[i] == pattern[k]) {
      ++k;
    }
    last = k;
  }
  return last;
}

std::string Concatenation(int32_t& n) {
  std::string string = " ";
  std::cin >> string;
  for (int32_t i = 0; i < n - 1; ++i) {
    std::string pattern = " ";
    std::cin >> pattern;
    std::vector<int32_t> pref(pattern.length(), 0);
    Prefix(pattern, pref);
    int32_t ans = KMP(string, pattern, pref);
    for (int32_t i = ans; i < static_cast<int32_t>(pattern.length()); ++i) {
      string += pattern[i];
    }
  }
  return string;
}

int main() {
  int32_t n = 0;
  std::cin >> n;
  std::cout << Concatenation(n) << "\n";
  return 0;
}
