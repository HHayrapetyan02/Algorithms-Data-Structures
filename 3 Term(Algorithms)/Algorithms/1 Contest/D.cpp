#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

std::string PrefConvertString(std::vector<int32_t>& pref) {
  std::string string(pref.size(), ' ');
  string[0] = 'a';
  for (size_t i = 1; i < pref.size(); ++i) {
    if (pref[i] > 0) {
      string[i] = string[pref[i] - 1];
    } else {
      std::unordered_set<char> banned;
      int32_t k = pref[i - 1];
      while (k > 0) {
        banned.emplace(string[k]);
        k = pref[k - 1];
      }
      for (char symbol = 'b'; symbol <= 'z'; ++symbol) {
        if (banned.find(symbol) == banned.end()) {
          string[i] = symbol;
          break;
        }
      }
    }
  }
  return string;
}

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

std::ostream& operator<<(std::ostream& os, std::vector<int32_t>& vec) {
  for (const auto elem : vec) {
    os << elem << " ";
  }
  os << "\n";
  return os;
}

int main() {
  int32_t n = 0;
  std::cin >> n;
  std::vector<int32_t> pref(n, 0);
  for (int32_t i = 0; i < n; ++i) {
    std::cin >> pref[i];
  }
  std::string str = PrefConvertString(pref);
  std::vector<int32_t> z(n, 0);
  ZFunction(str, z);
  std::cout << z << "\n";
  return 0;
}
