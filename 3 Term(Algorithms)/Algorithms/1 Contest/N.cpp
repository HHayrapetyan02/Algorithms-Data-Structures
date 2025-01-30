#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

struct Node {
  std::unordered_map<char, Node*> transitions;
  Node* suff_ref = nullptr;
  size_t len = 0;
  size_t end_pos = 0;
  size_t num = 0;
  bool visited = false;
  Node() = default;
};

class SuffixAutomaton {
  Node* root_ = new Node();
  Node* last_ = nullptr;
  int32_t count_ = 0;

 public:
  Node* Clone(Node*, const char&, Node*, const Node*&);
  void AddSymbol(const char&);
  explicit SuffixAutomaton(const std::string& str) {
    for (const auto& elem : str) {
      AddSymbol(elem);
    }
  }
  ~SuffixAutomaton();
};

Node* SuffixAutomaton::Clone(Node* parent, const char& c, Node* node, const Node*& copy_last) {
  Node* clone = new Node();
  ++count_;
  clone->transitions = node->transitions;
  clone->suff_ref = node->suff_ref;
  clone->len = parent->len + 1;
  clone->end_pos = copy_last->end_pos;
  clone->num = count_;
  node->suff_ref = clone;
  while (parent != nullptr && parent->transitions[c] == node) {
    parent->transitions[c] = clone;
    parent = parent->suff_ref;
  }
  return clone;
}

void SuffixAutomaton::AddSymbol(const char& c) {
  Node* new_node = new Node();
  ++count_;
  if (root_->transitions.empty()) {
    new_node->suff_ref = root_;
    new_node->end_pos = 1;
    new_node->len = 1;
    last_ = new_node;
    root_->transitions[c] = new_node;
    new_node->num = count_;
    return;
  }
  new_node->end_pos = last_->end_pos + 1;
  new_node->len = last_->len + 1;
  new_node->num = count_;
  const Node* copy_last = last_;
  while (last_ != nullptr && last_->transitions.find(c) == last_->transitions.end()) {
    last_->transitions[c] = new_node;
    last_ = last_->suff_ref;
  }
  if (last_ == nullptr) {
    new_node->suff_ref = root_;
  } else if (last_->len + 1 == last_->transitions[c]->len) {
    new_node->suff_ref = last_->transitions[c];
  } else {
    new_node->suff_ref = Clone(last_, c, last_->transitions[c], copy_last);
  }
  last_ = new_node;
}

SuffixAutomaton::~SuffixAutomaton() {
  std::cout << count_ + 1 << "\n";
  std::queue<Node*> queue;
  std::vector<Node*> removable;
  queue.emplace(root_);
  while (!queue.empty()) {
    Node* node = queue.front();
    queue.pop();
    if (!node->visited) {
      removable.emplace_back(node);
      for (const auto& elem : node->transitions) {
        std::cout << node->num << " " << elem.first << " " << elem.second->num << "\n";
        queue.emplace(elem.second);
      }
      node->visited = true;
    }
  }
  for (const auto& elem : removable) {
    delete elem;
  }
}

int main() {
  std::string str = " ";
  std::cin >> str;
  SuffixAutomaton suff_auto(str);
  return 0;
}
