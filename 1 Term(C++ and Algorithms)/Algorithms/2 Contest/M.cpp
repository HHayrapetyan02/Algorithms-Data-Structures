#include <iostream>
#include <cstring>

struct Node {
  int value = 0;
  int height = 1;
  Node* left = nullptr;
  Node* right = nullptr;
};

class AVL {
 public:
  int count = 0;
  Node* root = nullptr;
  int Height(Node* node);
  int Bfactor(Node* node);
  void FixHeight(Node* node);
  Node* RotateRight(Node* p);
  Node* RotateLeft(Node* q);
  Node* Balance(Node* p);
  Node* Insert(Node* r, int k);
  void Clear(Node* node);
  Node* Next(Node* root, int x);
  bool Exist(Node* node, int64_t x);
  Node* RemoveMin(Node* p);
  Node* Remove(Node* node, int k);
  Node* Find(Node* root, int k);
  Node* FindMin(Node* p);
  Node* FindMaX(Node* p);
};

Node* AVL::FindMin(Node* p) {
  return p->left ? FindMin(p->left) : p;
}

Node* AVL::FindMaX(Node* p) {
  return p->right ? FindMaX(p->right) : p;
}

Node* AVL::Find(Node* root, int k) {
  auto q = new Node;
  if (root != nullptr) {
    if (root->value == k) {
      q = root;
    } else if (k < root->value) {
      q = Find(root->left, k);
    } else {
      q = Find(root->right, k);
    }
  }
  return q;
}

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

void AVL::Clear(Node* node) {
  if (node != nullptr) {
    if ((node->left) != nullptr) {
      Clear(node->left);
    }
    if ((node->right) != nullptr) {
      Clear(node->right);
    }
  }
  delete node;
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

Node* AVL::RemoveMin(Node* p) {
  if (p->left == nullptr) {
    return p->right;
  }
  p->left = RemoveMin(p->left);
  return Balance(p);
}

Node* AVL::Remove(Node* node, int k) {
  if (node == nullptr) {
    return nullptr;
  }
  if (k < node->value) {
    node->left = Remove(node->left, k);
  } else if (k > node->value) {
    node->right = Remove(node->right, k);
  } else {
    Node* left = node->left;
    Node* right = node->right;
    delete node;
    node = nullptr;
    if (count == 0) {
      root = nullptr;
    }
    if (right == nullptr) {
      return left;
    }
    Node* min = FindMin(right);
    min->right = RemoveMin(right);
    min->left = left;
    return Balance(min);
  }
  return Balance(node);
}

int main() {
  AVL tree;
  int m = 0;
  std::cin >> m;
  auto command = new char[20]{};
  for (int i = 0; i < m; ++i) {
    scanf("%s", command);
    if (std::strcmp(command, "insert") == 0) {
      int tmp = 0;
      std::cin >> tmp;
      ++tree.count;
      tree.root = tree.Insert(tree.root, tmp);
      std::cout << "ok\n";
    } else if (std::strcmp(command, "extract_min") == 0) {
      if (tree.count == 0) {
        std::cout << "error\n";
      } else {
        int tmp = tree.FindMin(tree.root)->value;
        --tree.count;
        tree.root = tree.Remove(tree.root, tmp);
        std::cout << tmp << "\n";
      }
    } else if (std::strcmp(command, "get_min") == 0) {
      if (tree.count == 0) {
        std::cout << "error\n";
      } else {
        int tmp = tree.FindMin(tree.root)->value;
        std::cout << tmp << "\n";
      }
    } else if (std::strcmp(command, "extract_max") == 0) {
      if (tree.count == 0) {
        std::cout << "error\n";
      } else {
        int tmp = tree.FindMaX(tree.root)->value;
        --tree.count;
        tree.root = tree.Remove(tree.root, tmp);
        std::cout << tmp << "\n";
      }
    } else if (std::strcmp(command, "get_max") == 0) {
      if (tree.count == 0) {
        std::cout << "error\n";
      } else {
        int tmp = tree.FindMaX(tree.root)->value;
        std::cout << tmp << "\n";
      }
    } else if (std::strcmp(command, "size") == 0) {
      std::cout << tree.count << "\n";
    }
    if (std::strcmp(command, "clear") == 0) {
      tree.Clear(tree.root);
      tree.count = 0;
      tree.root = nullptr;
      std::cout << "ok\n";
    }
  }
  delete[] command;
  tree.Clear(tree.root);
  return 0;
}
