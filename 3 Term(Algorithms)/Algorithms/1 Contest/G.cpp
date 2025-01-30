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

std::pair<bool, int32_t> KMP(std::string& string, std::string& pattern, std::vector<int32_t>& pref) {
  int32_t last = 0;
  for (size_t i = 0; i < string.length(); ++i) {
    int32_t k = last;
    while (k > 0 && (k == static_cast<int32_t>(pattern.length()) || string[i] != pattern[k])) {
      k = pref[k - 1];
    }
    if (string[i] == pattern[k]) {
      ++k;
    }
    last = k;
    if (k == static_cast<int32_t>(pattern.length())) {
      return {std::pair<bool, int32_t>(true, i + 1)};
    }
  }
  return {std::pair<bool, int32_t>(false, -1)};
}

int main() {
  int32_t n = 0;
  std::cin >> n;
  std::string string = " ";
  std::string pattern = " ";
  std::cin >> string >> pattern;
  std::vector<int32_t> pref(pattern.length(), 0);
  Prefix(pattern, pref);
  std::string str_1 = "0" + string + "0" + string;
  std::string str_2 = "1" + string + "1" + string;
  std::pair<bool, int32_t> pair_1 = KMP(str_1, pattern, pref);
  std::pair<bool, int32_t> pair_2 = KMP(str_2, pattern, pref);
  if (pair_1.first && pair_2.first) {
    std::cout << "Random\n";
  } else if (pair_1.first) {
    if (str_1[pair_1.second] == '1') {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  } else {
    if (str_2[pair_2.second] == '1') {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  }
  return 0;
}
