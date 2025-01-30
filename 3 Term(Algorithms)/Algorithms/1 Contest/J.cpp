#include <iostream>
#include <vector>
#include <string>

void ZFunction(std::string& string, std::vector<int32_t>& z) {
  z[0] = static_cast<int32_t>(string.length());
  int32_t left = 0;
  int32_t right = 0;
  for (int32_t i = 1; i < static_cast<int32_t>(string.length()); ++i) {
    if (i < right) {
      z[i] = std::min(z[i - left], right - i);
    }
    while (i + z[i] < static_cast<int32_t>(string.length()) && string[z[i]] == string[i + z[i]]) {
      ++z[i];
    }
    if (i + z[i] > right) {
      left = i;
      right = i + z[i];
    }
  }
}

void Interesting(std::string& string, std::string& pattern) {
  std::string str = string + "#" + pattern;
  std::vector<int32_t> z(str.length(), 0);
  ZFunction(str, z);
  auto conc_len = static_cast<int32_t>(str.length());
  auto len = static_cast<int32_t>(string.length());
  int32_t end = conc_len - 1;
  int32_t count = 0;
  std::vector<std::string> pref;
  while (end > len) {
    int32_t tmp = end;
    while (z[end] == 0 || z[end] < tmp - end + 1) {
      --end;
      if (end == len) {
        break;
      }
    }
    if (end != len) {
      count += tmp - end + 1;
      std::string tmp_str(tmp - end + 1, ' ');
      for (int32_t i = end; i <= tmp; ++i) {
        tmp_str[i - end] = str[i];
      }
      pref.emplace_back(tmp_str);
      --end;
    }
  }
  if (count == static_cast<int32_t>(pattern.length())) {
    std::cout << "No\n";
    auto it = std::cend(pref);
    while (it != std::cbegin(pref)) {
      std::cout << *(--it) << ' ';
    }
  } else {
    std::cout << "Yes\n";
  }
}

int main() {
  std::string string = " ";
  std::string pattern = " ";
  std::cin >> string >> pattern;
  Interesting(string, pattern);
  return 0;
}
