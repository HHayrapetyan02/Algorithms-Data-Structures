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
  int TreeHeight(Node* root);
  void Clear(Node* root);
  int ShowHeight();
  void AllClear();
};

void BST::Insert(int value) {
  auto z = new Node;
  z->key = value;
  Node* y = nullptr;
  Node* x = this->root_;
  while (x != nullptr) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
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

int BST::TreeHeight(Node* root) {
  int left = 0;
  int right = 0;
  int height = 0;
  if (root != nullptr) {
    left = TreeHeight(root->left);
    right = TreeHeight(root->right);
    height = ((left > right ? left : right) + 1);
  }
  return height;
}

int BST::ShowHeight() {
  return TreeHeight(root_);
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
  int n = 0;
  BST tree;
  while (std::cin >> n && n != 0) {
    tree.Insert(n);
  }
  std::cout << tree.ShowHeight() << "\n";
  tree.AllClear();
  return 0;
}
