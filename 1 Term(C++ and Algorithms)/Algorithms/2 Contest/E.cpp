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
  void Transplant(Node* u, Node* v);
  void Delete(Node* u);
  Node* Minimum(Node* root);
  void InorderTraversal(Node* root);
  void ShowInorderTraversal();
};

void BST::InorderTraversal(Node* root) {
  int tmp = 0;
  if (root != nullptr) {
    if (root->left != nullptr) {
      ++tmp;
      InorderTraversal(root->left);
    }
    if (root->right != nullptr) {
      ++tmp;
      InorderTraversal(root->right);
    }
    if (tmp == 0) {
      std::cout << root->key << " ";
    }
  } else {
    std::cout << " ";
  }
}

void BST::ShowInorderTraversal() {
  return InorderTraversal(this->root_);
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

Node* BST::Minimum(Node* root) {
  if (root->left == nullptr || root == nullptr) {
    return root;
  }
  return Minimum(root->left);
}

void BST::Transplant(Node* u, Node* v) {
  if (u->parent == nullptr) {
    this->root_ = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if (v != nullptr) {
    v->parent = u->parent;
  }
}

void BST::Delete(Node* u) {
  if (u == nullptr) {
    delete u;
    return;
  }
  if (u->parent == nullptr) {
    Node* tmp = root_->left;
    delete root_;
    root_ = tmp;
    root_->parent = nullptr;
    return;
  }
  if (u->left == nullptr) {
    Transplant(u, u->right);
    delete u;
  } else if (u->right == nullptr) {
    Transplant(u, u->left);
    delete u;
  } else {
    Node* y = Minimum(u->right);
    if (y->parent != u) {
      Transplant(y, y->right);
      y->right = u->right;
      y->right->parent = y;
    }
    Transplant(u, y);
    y->left = u->left;
    y->left->parent = u;
    delete u;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  BST tree;
  while (std::cin >> n && n != 0) {
    tree.Insert(n);
  }
  tree.ShowInorderTraversal();
  tree.AllClear();
  return 0;
}
