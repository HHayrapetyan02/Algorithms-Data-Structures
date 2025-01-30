#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

struct Node {
  std::unordered_map<char, Node*> edges;
  bool is_terminal = false;
  Node* suff_ref = nullptr;
  Node* exit_link = nullptr;
  std::string str = " ";

  Node() = default;
  Node(const std::unordered_map<char, Node*>& edges, const bool& is_terminal, Node*& suff_ref, Node*& exit_link,
       std::string& str)
      : edges(edges), is_terminal(is_terminal), suff_ref(suff_ref), exit_link(exit_link), str(str) {
  }
};

class Trie {
  Node* root_ = new Node();

  struct NodeForSuffRef {
    char symbol = ' ';
    Node* parent = nullptr;
    Node* node = nullptr;

    NodeForSuffRef() = default;
    NodeForSuffRef(const char& sym, Node*& parent, Node*& node) : symbol(sym), parent(parent), node(node) {
    }
  };

 public:
  Node* ShowRoot() const {
    return root_;
  }
  Trie() = default;
  ~Trie();
  bool Find(const std::string&) const;
  void Insert(const std::string&);
  void ClearNode(Node*);
  void BuildSuffixReferences();
  void BuildExitLinks();
  Node* NextState(Node*&, const char&) const;
  void SaveEntries(int32_t&, Node*, std::unordered_map<std::string, std::vector<int32_t>>&);
};

bool Trie::Find(const std::string& string) const {
  Node* node = root_;
  for (const auto& symbol : string) {
    auto edge = node->edges[symbol];
    if (edge == nullptr) {
      return false;
    }
    node = edge;
  }
  return true;
}

void Trie::Insert(const std::string& string) {
  Node* node = root_;
  for (const auto& symbol : string) {
    auto edge = node->edges[symbol];
    if (edge == nullptr) {
      Node* new_node = new Node();
      node->edges[symbol] = new_node;
      node = new_node;
      new_node->str = node->str;
      edge = new_node;
    }
    node = edge;
  }
  node->is_terminal = true;
  node->str = string;
}

void Trie::BuildSuffixReferences() {
  std::queue<NodeForSuffRef> queue;
  for (auto elem : root_->edges) {
    queue.emplace(elem.first, root_, elem.second);
  }
  NodeForSuffRef tmp = {};
  while (!queue.empty()) {
    tmp = queue.front();
    queue.pop();
    Node* suff_parent = tmp.parent->suff_ref;
    while (suff_parent != nullptr && suff_parent->edges.find(tmp.symbol) == suff_parent->edges.end()) {
      suff_parent = suff_parent->suff_ref;
    }
    tmp.node->suff_ref = (suff_parent == nullptr ? root_ : suff_parent->edges[tmp.symbol]);
    for (auto pair : tmp.node->edges) {
      queue.emplace(pair.first, tmp.node, pair.second);
    }
  }
}

void Trie::BuildExitLinks() {
  std::queue<Node*> queue;
  for (auto elem : root_->edges) {
    queue.emplace(elem.second);
  }
  Node* node = nullptr;
  while (!queue.empty()) {
    node = queue.front();
    queue.pop();
    Node* suff = node->suff_ref;
    if (suff != root_) {
      node->exit_link = (suff->is_terminal ? suff : suff->exit_link);
    }
    for (auto pair : node->edges) {
      queue.emplace(pair.second);
    }
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
    for (const auto edge : node->edges) {
      ClearNode(edge.second);
    }
  }
  delete node;
}

Node* Trie::NextState(Node*& node, const char& symbol) const {
  while (node != nullptr && node->edges.find(symbol) == node->edges.end()) {
    node = node->suff_ref;
  }
  return (node == nullptr ? root_ : node->edges[symbol]);
}

void Trie::SaveEntries(int32_t& index, Node* node,
                       std::unordered_map<std::string, std::vector<int32_t>>& num_patterns) {
  if (!node->is_terminal) {
    node = node->exit_link;
  }
  while (node != nullptr) {
    num_patterns[node->str].emplace_back(index - static_cast<int32_t>(node->str.length()) + 2);
    node = node->exit_link;
  }
}

void AhoCorasick(const std::string& main_string, int32_t& n) {
  Trie trie;
  std::string pattern;
  std::unordered_map<std::string, std::vector<int32_t>> num_patterns;
  std::vector<std::string> patterns(n, " ");
  for (int32_t i = 0; i < n; ++i) {
    std::cin >> pattern;
    patterns[i] = pattern;
    trie.Insert(pattern);
  }
  trie.BuildSuffixReferences();
  trie.BuildExitLinks();
  Node* node = trie.ShowRoot();
  for (int32_t i = 0; i < static_cast<int32_t>(main_string.length()); ++i) {
    node = trie.NextState(node, main_string[i]);
    trie.SaveEntries(i, node, num_patterns);
  }
  for (const auto& str : patterns) {
    std::cout << num_patterns[str].size() << " ";
    for (const auto& index : num_patterns[str]) {
      std::cout << index << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  std::string main_string = " ";
  int32_t n = 0;
  std::cin >> main_string >> n;
  AhoCorasick(main_string, n);
  return 0;
}
