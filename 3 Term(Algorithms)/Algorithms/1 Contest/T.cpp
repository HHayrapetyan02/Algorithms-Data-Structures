#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

struct Node {
  bool is_terminal;
  std::string min;
  std::unordered_map<char, uint> map;
  int q = 0;
  uint depth = 0;
  Node() = default;
};

class Bor {
 public:
  std::vector<Node> nodes_;
  std::vector<uint_fast64_t> prices_;
  uint length_;
  uint system_;

  Bor(uint max, const std::vector<uint_fast64_t> &prices, uint system)
      : prices_(prices), length_(max), system_(system) {
  }
  void Add(const std::string &string) {
    if (nodes_.empty()) {
      Node to_ins;
      nodes_.emplace_back(to_ins);
    }
    uint cur = 0;
    for (uint idx = 0; idx < string.size(); ++idx) {
      if (nodes_[cur].map[string[idx]] == 0) {
        Node to_ins;
        nodes_.emplace_back(to_ins);
        nodes_[cur].map[string[idx]] = static_cast<uint>(nodes_.size() - 1);
      }
      cur = nodes_[cur].map[string[idx]];
      ++nodes_[cur].q;
      nodes_[cur].depth = idx + 1;
    }
    nodes_[cur].is_terminal = true;
  }
  void Count() {
    uint_fast64_t res = CountN(0);
    int add = static_cast<int>(length_) - static_cast<int>(nodes_[0].min.size());
    std::string add_str(add, '0');
    std::cout << nodes_[0].min + add_str << '\n';
    std::cout << res;
  }
  uint_fast64_t CountN(uint node) {
    if (nodes_[node].depth == length_) {
      return nodes_[node].q * prices_[length_ - 1];
    }
    if (nodes_[node].map.size() < system_) {
      for (char idx = '0'; static_cast<int>(idx) < static_cast<int>('0') + static_cast<int>(system_); ++idx) {
        if (nodes_[node].map[idx] == 0) {
          nodes_[node].min = idx;
        }
      }
      if (node == 0) {
        return 0;
      }
      return nodes_[node].q * prices_[nodes_[node].depth - 1];
    }
    uint_fast64_t min = 1000000000000000000;
    std::string min_str;
    for (auto &p : nodes_[node].map) {
      uint_fast64_t res = CountN(p.second);
      if (node != 0) {
        res += (nodes_[node].q - nodes_[p.second].q) * prices_[nodes_[node].depth - 1];
      }
      if (res <= min) {
        min = res;
        min_str = (p.first) + nodes_[p.second].min;
      }
    }
    nodes_[node].min = min_str;
    return min;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  uint size = 0;
  uint max = 0;
  uint system = 0;
  std::cin >> size >> max >> system;
  std::vector<uint_fast64_t> prices(max, 0);
  for (uint idx = 0; idx < max; ++idx) {
    std::cin >> prices[idx];
  }
  Bor bor(max, prices, system);
  for (uint idx = 0; idx < size; ++idx) {
    std::string string;
    std::cin >> string;
    bor.Add(string);
  }
  bor.Count();
  return 0;
}
