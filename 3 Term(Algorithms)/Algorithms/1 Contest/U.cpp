#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

inline bool IsPalindrom(const std::string &s, int i, int j) {
  while (i < j && s[i] == s[j]) {
    ++i;
    --j;
  }
  return i >= j;
}

struct Node {
  int is_terminal = 0;
  std::vector<int> map = std::vector<int>(26, 0);
  std::vector<int> set;
  Node() = default;
};

struct Pair {
  int first;
  int second;
  Pair(int s, int m) : first(s), second(m){};
};

class Bor {
 public:
  std::vector<Node> nodes_;

  Bor() = default;
  void Add(const std::string &string, int num) {
    if (nodes_.empty()) {
      Node to_ins;
      nodes_.emplace_back(to_ins);
    }
    int cur = 0;
    for (int idx = 0; idx < static_cast<int>(string.size()); ++idx) {
      if (nodes_[cur].map[static_cast<int>(string[static_cast<int>(string.size()) - 1 - idx] - 'a')] == 0) {
        Node to_ins;
        nodes_.emplace_back(to_ins);
        nodes_[cur].map[static_cast<int>(string[static_cast<int>(string.size()) - 1 - idx] - 'a')] =
            static_cast<int>(nodes_.size()) - 1;
      }
      cur = nodes_[cur].map[static_cast<int>(string[static_cast<int>(string.size()) - 1 - idx] - 'a')];
      if (IsPalindrom(string, 0, static_cast<int>(string.size()) - 2 - idx)) {
        nodes_[cur].set.emplace_back(num);
      }
    }
    nodes_[cur].is_terminal = num;
  }
  void Pairs(const std::vector<std::string> &words) {
    int64_t ans = 0;
    std::vector<Pair> pairs;
    pairs.reserve(1000000);
    for (int idx = 0; idx < static_cast<int>(words.size()); ++idx) {
      int cur = 0;
      for (int j = 0; j < static_cast<int>(words[idx].size()) && cur >= 0; ++j) {
        if (nodes_[cur].map[static_cast<int>(words[idx][j] - 'a')] != 0) {
          cur = nodes_[cur].map[static_cast<int>(words[idx][j] - 'a')];
          if (nodes_[cur].is_terminal != 0 && (j != static_cast<int>(words[idx].size()) - 1) &&
              (idx + 1 != nodes_[cur].is_terminal) &&
              IsPalindrom(words[idx], j + 1, static_cast<int>(words[idx].size()) - 1)) {
            ++ans;
            pairs.emplace_back(idx + 1, nodes_[cur].is_terminal);
          }
        } else {
          cur = -1;
          break;
        }
      }
      if (cur != -1) {
        for (auto &p : nodes_[cur].set) {
          if (idx + 1 != p) {
            pairs.emplace_back(idx + 1, p);
            ++ans;
          }
        }
      }
    }
    std::cout << ans << '\n';
    for (auto &p : pairs) {
      std::cout << p.first << ' ' << p.second << '\n';
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  Bor bor;
  std::vector<std::string> words(n);
  for (int idx = 0; idx < n; ++idx) {
    std::cin >> words[idx];
    bor.Add(words[idx], idx + 1);
  }
  bor.Pairs(words);
  return 0;
}
