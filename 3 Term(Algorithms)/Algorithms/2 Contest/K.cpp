#include <iostream>
#include <vector>
#include <random>

std::mt19937 rnd(987654321);

struct Node {
  int64_t sum;
  int value;
  uint y;
  Node* left;
  Node* right;
  Node() = default;
  explicit Node(int val) {
    sum = val;
    value = val;
    y = rnd();
    left = nullptr;
    right = nullptr;
  }
};

class InsertTree {
 public:
  Node* root_ = nullptr;
  InsertTree() = default;
  void Update(Node* t) {
    t->sum = t->value + Getsum(t->left) + Getsum(t->right);
  }
  int GetValue(Node* t) {
    if (t == nullptr) {
      return 0;
    }
    return t->value;
  }
  int64_t Getsum(Node* t) {
    if (t == nullptr) {
      return 0;
    }
    return t->sum;
  }
  void Split(Node*& t_1, Node*& t_2, Node* t, int x, bool& flag) {
    if (t == nullptr) {
      t_1 = t_2 = nullptr;
      return;
    }
    if (t->value == x) {
      flag = true;
    }
    if (t->value < x) {
      Split(t->right, t_2, t->right, x, flag);
      t_1 = t;
      Update(t);
    } else {
      Split(t_1, t->left, t->left, x, flag);
      t_2 = t;
      Update(t);
    }
  }
  Node* Merge(Node* t_1, Node* t_2) {
    if (t_1 == nullptr) {
      return t_2;
    }
    if (t_2 == nullptr) {
      return t_1;
    }
    if (t_1->y < t_2->y) {
      t_1->right = Merge(t_1->right, t_2);
      Update(t_1);
      return t_1;
    }
    t_2->left = Merge(t_1, t_2->left);
    Update(t_2);
    return t_2;
  }
  void Insert(int value) {
    Node* t_1 = nullptr;
    Node* t_2 = nullptr;
    bool exist = false;
    Split(t_1, t_2, root_, value, exist);
    if (!exist) {
      Node* node = new Node(value);
      root_ = Merge(Merge(t_1, node), t_2);
      return;
    }
    root_ = Merge(t_1, t_2);
  }
  int64_t Query(int l, int r) {
    Node* t_1 = nullptr;
    Node* t_2 = nullptr;
    Node* t_3 = nullptr;
    Node* t_4 = nullptr;
    bool b = false;
    Split(t_1, t_2, root_, r + 1, b);
    Split(t_3, t_4, t_1, l, b);
    if (t_4 == nullptr) {
      root_ = Merge(Merge(t_3, t_4), t_2);
      return 0;
    }
    int64_t ans = t_4->sum;
    root_ = Merge(Merge(t_3, t_4), t_2);
    return ans;
  }
  void Delete(Node* node) {
    if (node == nullptr) {
      return;
    }
    Delete(node->left);
    Delete(node->right);
    delete node;
  }
  void Print(Node* tree) {
    if (tree == nullptr) {
      return;
    }
    Print(tree->left);
    std::cout << tree->value << " ";
    Print(tree->right);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  InsertTree tree;
  int n = 0;
  std::cin >> n;
  for (int idx = 0; idx < n; ++idx) {
    char com = 'd';
    std::cin >> com;
    if (com == '?') {
      int l = 0;
      int r = 0;
      std::cin >> l >> r;
      std::cout << tree.Query(l, r) << '\n';
    } else {
      int val = 0;
      std::cin >> val;
      tree.Insert(val);
    }
  }
  tree.Delete(tree.root_);
  return 0;
}
