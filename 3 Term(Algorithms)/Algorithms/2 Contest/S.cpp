#include <iostream>
#include <vector>

struct Node {
  Node* left = nullptr;
  Node* right = nullptr;
  int priority = 0;
  int value = 0;
  int min = 0;
  int size = 0;
  bool flag_reversed = false;

  Node() = default;

  explicit Node(int x) : value(x) {
    priority = std::rand();
    size = 1;
    min = value;
  }
};

int GetSize(const Node* node) {
  return node == nullptr ? 0 : node->size;
}

void UpdateSize(Node* node) {
  if (node != nullptr) {
    node->size = GetSize(node->left) + GetSize(node->right) + 1;
  }
}

int GetMin(const Node* node) {
  return node == nullptr ? static_cast<int>(1e9) : node->min;
}

void UpdateMin(Node* node) {
  if (node != nullptr) {
    int min_left = GetMin(node->left);
    int min_right = GetMin(node->right);
    int temp_min = min_left > min_right ? min_right : min_left;
    node->min = temp_min > node->value ? node->value : temp_min;
  }
}

void SetPromise(Node* node) {
  if (node != nullptr) {
    node->flag_reversed = !node->flag_reversed;
  }
}

void Push(Node* node) {
  if (node != nullptr) {
    if (node->flag_reversed) {
      Node* temp = node->left;
      node->left = node->right;
      SetPromise(node->left);
      node->right = temp;
      SetPromise(node->right);
      node->flag_reversed = false;
    }
  }
}

class Treap {
  Node* root_ = nullptr;

 public:
  Treap() = default;
  ~Treap() {
    while (root_ != nullptr) {
      Delete(root_, 0);
    }
  }
  explicit Treap(Node* root) : root_(root) {
  }

  Node* Merge(Node* t1, Node* t2) {
    if (t1 == nullptr) {
      return t2;
    }
    if (t2 == nullptr) {
      return t1;
    }
    if (t2->priority < t1->priority) {
      Push(t2);
      t2->left = Merge(t1, t2->left);
      UpdateSize(t2);
      UpdateMin(t2);
      return t2;
    }
    Push(t1);
    t1->right = Merge(t1->right, t2);
    UpdateSize(t1);
    UpdateMin(t1);
    return t1;
  }

  std::pair<Node*, Node*> Split(Node* t, int k) {
    Push(t);
    if (t == nullptr) {
      return {nullptr, nullptr};
    }
    int left_size = GetSize(t->left);
    if (left_size < k) {
      auto pair = Split(t->right, k - left_size - 1);
      t->right = pair.first;
      UpdateSize(t);
      UpdateMin(t);
      return {t, pair.second};
    }
    auto pair = Split(t->left, k);
    t->left = pair.second;
    UpdateSize(t);
    UpdateMin(t);
    return {pair.first, t};
  }

  void Insert(int k, int value) {
    Node* node = new Node(value);
    if (root_ == nullptr) {
      root_ = node;
      return;
    }
    std::pair<Node*, Node*> pair = Split(root_, k);
    root_ = Merge(Merge(pair.first, node), pair.second);
  }

  int Min(const int l, const int r) {
    auto p1 = Split(root_, l);
    auto p2 = Split(p1.second, r - l);
    Push(p2.first);
    int min = GetMin(p2.first);
    root_ = Merge(Merge(p1.first, p2.first), p2.second);
    return min;
  }

  void Delete(Node* now_node, int k) {
    auto p1 = Split(now_node, k);
    auto p2 = Split(p1.second, 1);
    root_ = Merge(p1.first, p2.second);
    delete p2.first;
  }

  void Reverse(int l, int r) {
    auto p1 = Split(root_, l);
    auto p2 = Split(p1.second, r - l);
    if (p2.first != nullptr) {
      p2.first->flag_reversed = !p2.first->flag_reversed;
    }
    root_ = Merge(Merge(p1.first, p2.first), p2.second);
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Treap tree;
  int elem = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> elem;
    tree.Insert(i, elem);
  }
  int q = 0;
  int a = 0;
  int b = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> q >> a >> b;
    if (q == 1) {
      tree.Reverse(a - 1, b);
    } else if (q == 2) {
      std::cout << tree.Min(a - 1, b) << '\n';
    }
  }
  return 0;
}
