#include <iostream>

struct Node {
  int64_t key = 0;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

class BST {
  Node* root_ = nullptr;

 public:
  void Insert(int value);
  void Clear(Node* root);
  void AllClear();
  void InorderTraversal();
};

void BST::InorderTraversal() {
  if (this->root_ == nullptr) {
    return;
  }
  Node* v = this->root_;
  while (v != nullptr) {
    if (v->left == nullptr) {
      std::cout << v->key << "\n";
      v = v->right;
    } else {
      Node* q = v->left;
      while (q->right != nullptr && q->right != v) {
        q = q->right;
      }
      if (q->right == nullptr) {
        q->right = v;
        v = v->left;
      } else {
        q->right = nullptr;
        std::cout << v->key << "\n";
        v = v->right;
      }
    }
  }
}

void BST::Insert(int value) {
  auto z = new Node;
  z->key = value;
  Node* y = nullptr;
  Node* x = this->root_;
  while (x != nullptr) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else if (z->key > x->key) {
      x = x->right;
    } else {
      delete z;
      return;
    }
  }
  z->parent = y;
  if (y == nullptr) {
    this->root_ = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
}

void BST::Clear(Node* root) {
  if (root != nullptr) {
    if (root->left != nullptr) {
      Clear(root->left);
    }
    if (root->right != nullptr) {
      Clear(root->right);
    }
    delete root;
  }
}

void BST::AllClear() {
  return Clear(root_);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  BST tree;
  while (std::cin >> n && n != 0) {
    tree.Insert(n);
  }
  tree.InorderTraversal();
  tree.AllClear();
  return 0;
}
