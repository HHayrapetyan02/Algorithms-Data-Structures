#include <iostream>
#include <cstring>

struct Node {
  Node* prev = nullptr;
  int value = 0;
  int min = 0;
};

class Stack {
  Node* last_ = nullptr;
  int size_stack_ = 0;

 public:
  void Push(int k);
  int Pop();
  int Size();
  void Clear();
  int Front();
  int Min();
};

int Stack::Front() {
  int tmp = Pop();
  Push(tmp);
  return tmp;
}

void Stack::Push(int k) {
  auto q = new Node;
  q->value = k;
  if (size_stack_ == 0) {
    this->last_ = q;
    this->last_->value = k;
    this->last_->min = k;
    ++(this->size_stack_);
    return;
  }
  if (this->last_->min > k) {
    q->min = k;
  } else {
    q->min = this->last_->min;
  }
  q->prev = this->last_;
  this->last_ = q;
  ++(this->size_stack_);
}

int Stack::Pop() {
  Node* temp = this->last_;
  int value = this->last_->value;
  this->last_ = this->last_->prev;
  delete temp;
  --(this->size_stack_);
  return value;
}

void Stack::Clear() {
  if (Size() > 1) {
    Pop();
    Clear();
  }
  if (Size() == 1) {
    Pop();
  }
}

int Stack::Size() {
  return this->size_stack_;
}

int Stack::Min() {
  return this->last_->min;
}

class Queue {
 public:
  Stack stack1;
  Stack stack2;
  void Enqueue(int val);
  int Dequeue();
  int Size();
  int Front();
  void Clear();
  int Min();
};

int Queue::Front() {
  if (stack2.Size() == 0) {
    size_t len = stack1.Size();
    for (size_t i = 0; i < len; ++i) {
      int tmp = stack1.Pop();
      stack2.Push(tmp);
    }
    return stack2.Front();
  }
  return stack2.Front();
}

void Queue::Enqueue(int val) {
  stack1.Push(val);
}

int Queue::Dequeue() {
  if (stack2.Size() == 0) {
    size_t len = stack1.Size();
    for (size_t i = 0; i < len; ++i) {
      int tmp = stack1.Pop();
      stack2.Push(tmp);
    }
    return stack2.Pop();
  }
  return stack2.Pop();
}

int Queue::Size() {
  return stack1.Size() + stack2.Size();
}

void Queue::Clear() {
  stack1.Clear();
  stack2.Clear();
}

int Queue::Min() {
  if (stack1.Size() == 0) {
    return stack2.Min();
  }
  if (stack2.Size() == 0) {
    return stack1.Min();
  }
  return std::min(stack1.Min(), stack2.Min());
}

int main() {
  Queue queue;
  int m = 0;
  std::cin >> m;
  auto command = new char[20]{};
  for (int64_t i = 0; i < m; ++i) {
    scanf("%s", command);
    if (strcmp(command, "enqueue") == 0) {
      int tmp = 0;
      std::cin >> tmp;
      queue.Enqueue(tmp);
      std::cout << "ok\n";
    } else if (strcmp(command, "dequeue") == 0) {
      if (queue.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << queue.Dequeue() << '\n';
      }
    } else if (strcmp(command, "front") == 0) {
      if (queue.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << queue.Front() << '\n';
      }
    } else if (strcmp(command, "size") == 0) {
      std::cout << queue.Size() << '\n';
    } else if (strcmp(command, "clear") == 0) {
      queue.Clear();
      std::cout << "ok\n";
    } else if (strcmp(command, "min") == 0) {
      if (queue.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << queue.Min() << '\n';
      }
    }
  }
  queue.Clear();
  delete[] command;
}
