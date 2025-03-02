#include <iostream>
#include <vector>

struct Point {
  int key = 0;
  int priority = 0;

  Point() = default;
  Point(int key, int priority) : key(key), priority(priority){};
};

struct Node {
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  int cnt = 0;
  int key = 0;
  int priority = 0;

  Node() = default;
  explicit Node(Point point, int cnt = 0) : cnt(cnt), key(point.key), priority(point.priority){};
};

class Treap {
  Node* root_ = nullptr;
  std::vector<Node*> array_nodes_pointer_;

 public:
  Treap() = default;

  ~Treap() {
    for (size_t i = 1; i < array_nodes_pointer_.size(); ++i) {
      delete array_nodes_pointer_[i];
    }
  }

  explicit Treap(Node* root) : root_(root) {
  }

  void Build(Node* node, const std::vector<Point>& points) {
    array_nodes_pointer_.emplace_back(root_);
    for (size_t i = 1; i < points.size(); ++i) {
      Node* now_node = new Node(points[i]);
      now_node->cnt = static_cast<int>(i + 1);
      if (node->priority < now_node->priority) {
        node->right = now_node;
        now_node->parent = node;
      } else {
        while (node->parent != nullptr && node->priority > now_node->priority) {
          node = node->parent;
        }
        if (node->priority < now_node->priority) {
          Node* right_son = node->right;
          node->right = now_node;
          now_node->parent = node;
          now_node->left = right_son;
          if (right_son != nullptr) {
            right_son->parent = now_node;
          }
        } else {
          now_node->left = node;
          node->parent = now_node;
          root_ = now_node;
        }
      }
      array_nodes_pointer_.emplace_back(now_node);
      node = now_node;
    }
  }

  void PrintLinks() {
    std::cout << "YES\n";
    for (size_t i = 0; i < array_nodes_pointer_.size(); ++i) {
      Node* node = array_nodes_pointer_[i];
      if (node->parent == nullptr) {
        std::cout << 0 << ' ';
      } else {
        std::cout << node->parent->cnt << ' ';
      }
      if (node->left == nullptr) {
        std::cout << 0 << ' ';
      } else {
        std::cout << node->left->cnt << ' ';
      }
      if (node->right == nullptr) {
        std::cout << 0 << '\n';
      } else {
        std::cout << node->right->cnt << '\n';
      }
    }
  }
};

std::istream& operator>>(std::istream& is, std::vector<Point>& points) {
  for (size_t i = 0; i < points.size(); ++i) {
    is >> points[i].key >> points[i].priority;
  }
  return is;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Point> points(n);
  std::cin >> points;
  Node root(points[0], 1);
  Treap tree(&root);
  tree.Build(&root, points);
  tree.PrintLinks();
  return 0;
}
