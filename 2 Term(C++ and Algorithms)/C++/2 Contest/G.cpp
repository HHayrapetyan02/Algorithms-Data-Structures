#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

bool Comparator(const std::pair<std::string, int>& one, const std::pair<std::string, int>& two) {
  if (one.second > two.second) {
    return true;
  }
  if (one.second == two.second) {
    return one.first < two.first;
  }
  return false;
}

int main() {
  std::map<std::string, int> map;
  std::vector<std::pair<std::string, int>> vec;
  std::string word = " ";
  while (std::cin >> word) {
    ++map[word];
  }
  for (const auto& v : map) {
    std::pair<std::string, int> p;
    p = std::make_pair(v.first, v.second);
    vec.emplace_back(p);
  }
  std::sort(vec.begin(), vec.end(), Comparator);
  for (const auto& elem : vec) {
    std::cout << elem.first << "\n";
  }
  return 0;
}
