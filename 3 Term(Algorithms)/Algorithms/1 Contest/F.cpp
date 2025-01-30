#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int32_t Prefix(std::string& string) {
  int32_t max = 0;
  std::vector<int32_t> pref(string.length(), 0);
  for (int32_t i = 1; i < static_cast<int32_t>(string.length()); ++i) {
    int32_t k = pref[i - 1];
    while (string[i] != string[k] && k > 0) {
      k = pref[k - 1];
    }
    if (string[i] == string[k]) {
      pref[i] = k + 1;
      max = std::max(max, pref[i]);
    }
  }
  return max;
}

int32_t PrefixReversed(std::string& string, int32_t& right) {
  std::string tmp(right + 1, ' ');
  for (int32_t i = 0; i < right + 1; ++i) {
    tmp[i] = string[i];
  }
  std::reverse(tmp.begin(), tmp.end());
  return static_cast<int32_t>(tmp.length()) - Prefix(tmp);
}

int32_t DiffSubStr(std::string& string) {
  int count = 1;
  for (int32_t i = 1; i < static_cast<int32_t>(string.length()); ++i) {
    count += PrefixReversed(string, i);
  }
  return count;
}

int main() {
  std::string string = " ";
  std::cin >> string;
  std::cout << DiffSubStr(string) << "\n";
  return 0;
}
