#include <iostream>
#include <cstring>

struct Node {
  Node* prev = nullptr;
  char value;
};

class Stack {
  Node* last_ = nullptr;
  int stack_size_ = 0;

 public:
  int Size();
  char Pop();
  void Push(char k);
  void Clear();
  bool Empty();
};

int Stack::Size() {
  return this->stack_size_;
}

char Stack::Pop() {
  if (stack_size_ == 0) {
    return 0;
  }
  Node* q = this->last_;
  char val = this->last_->value;
  this->last_ = this->last_->prev;
  delete q;
  --(stack_size_);
  return val;
}

void Stack::Push(char k) {
  Node* q = new Node;
  q->value = k;
  q->prev = this->last_;
  this->last_ = q;
  ++(stack_size_);
}

void Stack::Clear() {
  if (Size() == 1) {
    Pop();
  }
  if (Size() > 1) {
    Pop();
    Clear();
  }
}

bool Stack::Empty() {
  return this->stack_size_ == 0;
}

int main() {
  Stack stack;
  char symbol = ' ';
  while (std::cin >> symbol) {
    if (symbol == '(' || symbol == '[' || symbol == '{') {
      stack.Push(symbol);
    } else if (symbol == ')') {
      char q = stack.Pop();
      if (q != '(') {
        std::cout << "NO";
        stack.Clear();
        return 0;
      }
    } else if (symbol == ']') {
      char q = stack.Pop();
      if (q != '[') {
        std::cout << "NO";
        stack.Clear();
        return 0;
      }
    } else {
      char q = stack.Pop();
      if (q != '{') {
        std::cout << "NO";
        stack.Clear();
        return 0;
      }
    }
  }
  if (stack.Empty()) {
    std::cout << "YES";
  } else {
    stack.Clear();
    std::cout << "NO";
  }
  return 0;
}
