#include <iostream>
#include <string>
#include <vector>

void ZConvertPref(int n, std::vector<int>& z, std::vector<int>& pref) {
  for (int i = 1; i < n; ++i) {
    for (int delta = z[i] - 1; delta >= 0; --delta) {
      if (pref[i + delta] > 0) {
        break;
      }
      pref[i + delta] = delta + 1;
    }
  }
}

std::ostream& operator<<(std::ostream& os, std::vector<int>& vec) {
  for (const auto elem : vec) {
    os << elem << " ";
  }
  os << "\n";
  return os;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int> z(n, 0);
  for (int i = 0; i < n; ++i) {
    std::cin >> z[i];
  }
  std::vector<int> pref(n, 0);
  ZConvertPref(n, z, pref);
  std::cout << pref << "\n";
  return 0;
}
