#include <iostream>

struct Node {
  int value = 0;
  int height = 1;
  Node* left = nullptr;
  Node* right = nullptr;
};

class AVL {
 public:
  Node* root = nullptr;
  int Height(Node* node);
  int Bfactor(Node* node);
  void FixHeight(Node* node);
  Node* RotateRight(Node* p);
  Node* RotateLeft(Node* q);
  Node* Balance(Node* p);
  Node* Insert(Node* r, int k);
  void Clear(Node* root);
  Node* Next(Node* root, int x);
  bool Exist(Node* node, int64_t x);
};

Node* AVL::Next(Node* root, int x) {
  if (root == nullptr) {
    return nullptr;
  }
  if (root->value == x) {
    return root;
  }
  if (x < root->value) {
    Node* next = Next(root->left, x);
    if (next == nullptr) {
      return root;
    }
    return next;
  }
  return Next(root->right, x);
}

bool AVL::Exist(Node* node, int64_t x) {
  if (node == nullptr) {
    return true;
  }
  if (node->value == x) {
    return false;
  }
  if (node->value > x) {
    return Exist(node->left, x);
  }
  return Exist(node->right, x);
}

void AVL::Clear(Node* root) {
  if (root != nullptr) {
    if ((root->left) != nullptr) {
      Clear(root->left);
    }
    if ((root->right) != nullptr) {
      Clear(root->right);
    }
    delete root;
  }
}

int AVL::Height(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int AVL::Bfactor(Node* node) {
  return Height(node->right) - Height(node->left);
}

void AVL::FixHeight(Node* node) {
  int height_left = Height(node->left);
  int height_right = Height(node->right);
  node->height = std::max(height_left, height_right) + 1;
}

Node* AVL::RotateRight(Node* p) {
  Node* q = p->left;
  p->left = q->right;
  q->right = p;
  FixHeight(p);
  FixHeight(q);
  return q;
}

Node* AVL::RotateLeft(Node* q) {
  Node* p = q->right;
  q->right = p->left;
  p->left = q;
  FixHeight(q);
  FixHeight(p);
  return p;
}

Node* AVL::Balance(Node* p) {
  FixHeight(p);
  if (Bfactor(p) == 2) {
    if (Bfactor(p->right) == -1) {
      p->right = RotateRight(p->right);
    }
    return RotateLeft(p);
  }
  if (Bfactor(p) == -2) {
    if (Bfactor(p->left) == 1) {
      p->left = RotateLeft(p->left);
    }
    return RotateRight(p);
  }
  return p;
}

Node* AVL::Insert(Node* r, int k) {
  if (r == nullptr) {
    auto cur = new Node;
    cur->value = k;
    return cur;
  }
  if (k < r->value) {
    r->left = Insert(r->left, k);
  } else {
    r->right = Insert(r->right, k);
  }
  return Balance(r);
}

int main() {
  AVL tree;
  int n = 0;
  int tmp = -2;
  std::cin >> n;
  int num = 1e9;
  int y = 0;
  for (int i = 0; i < n; ++i) {
    char command = ' ';
    int value = 0;
    std::cin >> command >> value;
    if (command == '+') {
      if (tmp == i - 1) {
        if (tree.Exist(tree.root, (value + y) % num)) {
          tree.root = tree.Insert(tree.root, (value + y) % num);
        }
      } else {
        if (tree.Exist(tree.root, value)) {
          tree.root = tree.Insert(tree.root, value);
        }
      }
    } else {
      Node* q = tree.Next(tree.root, value);
      if (q == nullptr) {
        std::cout << -1 << '\n';
        tmp = i;
        y = -1;
      } else {
        std::cout << q->value << '\n';
        tmp = i;
        y = q->value;
      }
    }
  }
  tree.Clear(tree.root);
  return 0;
}
