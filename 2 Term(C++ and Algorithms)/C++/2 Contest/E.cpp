#include <iostream>
#include <unordered_map>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  int n = 0;
  int q = 0;
  std::cin >> n;
  std::unordered_map<std::string, std::string> map(n);
  for (int i = 0; i < n; ++i) {
    std::string first = " ";
    std::string second = " ";
    std::cin >> first >> second;
    map[first] = second;
    map[second] = first;
  }
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::string synonim = " ";
    std::cin >> synonim;
    std::cout << map.at(synonim) << "\n";
  }
  return 0;
}
