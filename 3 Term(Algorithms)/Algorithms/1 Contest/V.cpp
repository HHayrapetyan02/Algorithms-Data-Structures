#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

struct Node {
  int is_terminal = 0;
  std::unordered_map<char, int> map;
  size_t max_size = 0;
  int max_node = 0;
  Node() = default;
};

class Bor {
  std::vector<Node> nodes_;
  std::vector<char> prints_;
  int64_t number_ = 0;
  size_t largest_ = 0;
  size_t out_ = 0;
  size_t words_ = 0;

 public:
  Bor() = default;
  void Add(const std::string &string) {
    ++words_;
    largest_ = std::max(largest_, string.size());
    if (nodes_.empty()) {
      Node to_ins;
      nodes_.emplace_back(to_ins);
    }
    int cur = 0;
    for (uint idx = 0; idx < string.size(); ++idx) {
      if (nodes_[cur].map[string[idx]] == 0) {
        Node to_ins;
        nodes_.emplace_back(to_ins);
        nodes_[cur].map[string[idx]] = static_cast<int>(nodes_.size() - 1);
      }
      if (nodes_[cur].max_size < static_cast<size_t>(string.size() - idx)) {
        nodes_[cur].max_size = static_cast<size_t>(string.size() - idx);
        nodes_[cur].max_node = nodes_[cur].map[string[idx]];
      }
      cur = nodes_[cur].map[string[idx]];
    }
    ++nodes_[cur].is_terminal;
  }
  void Print(int node) {
    if (nodes_[node].map.empty()) {
      for (int idx = 0; idx < nodes_[node].is_terminal; ++idx) {
        prints_.emplace_back('P');
        ++out_;
        ++number_;
      }
      if (out_ != words_) {
        prints_.emplace_back('-');
        ++number_;
      }
      return;
    }
    if (nodes_[node].is_terminal > 0) {
      for (int idx = 0; idx < nodes_[node].is_terminal; ++idx) {
        prints_.emplace_back('P');
        ++number_;
        ++out_;
      }
    }
    int last = 0;
    char last_char = '1';
    for (auto &p : nodes_[node].map) {
      if (p.second == nodes_[node].max_node) {
        last = p.second;
        last_char = p.first;
        continue;
      }
      prints_.emplace_back(p.first);
      ++number_;
      Print(p.second);
    }
    prints_.emplace_back(last_char);
    ++number_;
    Print(last);
    if (out_ != words_) {
      prints_.emplace_back('-');
      ++number_;
    }
    if (node == 0) {
      std::cout << number_ << '\n';
      for (auto &p : prints_) {
        std::cout << p << '\n';
      }
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Bor bor;
  int size = 0;
  std::cin >> size;
  for (int idx = 0; idx < size; ++idx) {
    std::string word;
    std::cin >> word;
    bor.Add(word);
  }
  bor.Print(0);
  return 0;
}
