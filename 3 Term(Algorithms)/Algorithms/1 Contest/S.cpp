#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

struct Node {
  std::unordered_map<char, Node*> edges;
  bool is_terminal = false;
  std::string town;
  int32_t len = 0;
  Node() = default;
};

class Trie {
  Node* root_ = new Node();
  std::vector<int32_t> lens_;
  std::unordered_map<std::string, int32_t> cakes_;

 public:
  Trie() = default;
  explicit Trie(const int32_t& m) {
    int32_t max_len = 1;
    lens_.resize(m);
    lens_[0] = 1;
    for (int32_t i = 0; i < m - 1; ++i) {
      max_len *= 10;
      lens_[i + 1] = max_len;
    }
  }
  ~Trie();
  bool Find(const std::string&) const;
  void Insert(const std::string&, const std::string&);
  void ClearNode(Node*);
  void Cakes();
};

void Trie::Cakes() {
  std::queue<std::pair<Node*, std::string>> queue;
  queue.emplace(root_, "");
  while (!queue.empty()) {
    Node* node = queue.front().first;
    std::string town = queue.front().second;
    queue.pop();
    if (node->is_terminal) {
      town = node->town;
    }
    if (!town.empty()) {
      int32_t len = static_cast<int32_t>(lens_.size()) - node->len - 1;
      if (node->len > static_cast<int32_t>(lens_.size())) {
        cakes_[town] += 0;
      } else if (node->len == static_cast<int32_t>(lens_.size())) {
        cakes_[town] += 1;
      } else {
        cakes_[town] += static_cast<int32_t>(lens_[len]) * (10 - static_cast<int32_t>(node->edges.size()));
      }
    }
    for (const auto& symbol : node->edges) {
      queue.emplace(symbol.second, town);
    }
  }
  for (const auto& town_and_cakes : cakes_) {
    std::cout << town_and_cakes.first << ' ' << town_and_cakes.second << '\n';
  }
}

Trie::~Trie() {
  if (root_ != nullptr) {
    for (const auto& edge : root_->edges) {
      ClearNode(edge.second);
    }
  }
  delete root_;
}

void Trie::ClearNode(Node* node) {
  if (node != nullptr) {
    for (const auto& edge : node->edges) {
      ClearNode(edge.second);
    }
  }
  delete node;
}

void Trie::Insert(const std::string& string, const std::string& town) {
  cakes_[town] = 0;
  Node* now_node = root_;
  int32_t len = 0;
  for (const auto& symbol : string) {
    auto edge = now_node->edges[symbol];
    if (edge == nullptr) {
      ++len;
      Node* new_node = new Node();
      now_node->edges[symbol] = new_node;
      new_node->len = len;
      now_node = new_node;
      edge = new_node;
    }
    now_node = edge;
    len = now_node->len;
  }
  now_node->is_terminal = true;
  now_node->town = town;
  now_node->len = len;
}

int main() {
  int32_t n = 0;
  int32_t m = 0;
  std::cin >> n >> m;
  Trie trie(m);
  std::string town = " ";
  std::string index = " ";
  for (int32_t i = 0; i < n; ++i) {
    std::cin >> index >> town;
    trie.Insert(index, town);
  }
  trie.Cakes();
  return 0;
}
