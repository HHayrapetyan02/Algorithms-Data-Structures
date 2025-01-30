#include <iostream>
#include <map>
#include <set>
#include <string>

int main() {
  std::string str = " ";
  std::map<std::string, std::map<std::string, int64_t>> map;
  std::set<std::string> names;
  while (std::cin >> str) {
    std::string product = " ";
    int64_t count = 0;
    std::cin >> product >> count;
    names.emplace(str);
    map[str][product] += count;
  }
  for (const auto& name : names) {
    std::cout << name << ':' << '\n';
    for (const auto& product : map[name]) {
      std::cout << product.first << ' ' << product.second << '\n';
    }
  }
  return 0;
}
