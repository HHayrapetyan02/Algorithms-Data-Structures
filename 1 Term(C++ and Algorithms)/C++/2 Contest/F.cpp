#include <iostream>

struct Node {
  Node* prev = nullptr;
  int value = 0;
};

class Stack {
  Node* last_ = nullptr;
  int stack_size_ = 0;

 public:
  void Push(int k);
  void Clear();
  int Pop();
  int Size();
  int Front();
  bool Empty();
};

void Stack::Push(int k) {
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

int Stack::Front() {
  int tmp = Pop();
  Push(tmp);
  return tmp;
}

int Stack::Pop() {
  if (stack_size_ == 0) {
    return 0;
  }
  auto q = this->last_;
  int val = this->last_->value;
  this->last_ = this->last_->prev;
  delete q;
  --(stack_size_);
  return val;
}

int Stack::Size() {
  return this->stack_size_;
}

bool Stack::Empty() {
  return stack_size_ == 0;
}

class Queue {
 public:
  Stack stack_1;
  Stack stack_2;
  void Enqueue(int k);
  void Clear();
  int Dequeue();
  int Size();
  int Front();
};

void Queue::Enqueue(int k) {
  stack_1.Push(k);
}

void Queue::Clear() {
  stack_1.Clear();
  stack_2.Clear();
}

int Queue::Size() {
  return stack_1.Size() + stack_2.Size();
}

int Queue::Dequeue() {
  if (stack_2.Empty()) {
    int len = stack_1.Size();
    for (int i = 0; i < len; ++i) {
      int tmp = stack_1.Pop();
      stack_2.Push(tmp);
    }
    return stack_2.Pop();
  }
  return stack_2.Pop();
}

int Queue::Front() {
  if (stack_2.Empty()) {
    int len = stack_1.Size();
    for (int i = 0; i < len; ++i) {
      int tmp = stack_1.Pop();
      stack_2.Push(tmp);
    }
    return stack_2.Front();
  }
  return stack_2.Front();
}

int main() {
  int count = 0;
  Queue queue_1;
  Queue queue_2;

  for (int i = 0; i < 5; ++i) {
    int n = 0;
    std::cin >> n;
    queue_1.Enqueue(n);
  }

  for (int i = 0; i < 5; ++i) {
    int n = 0;
    std::cin >> n;
    queue_2.Enqueue(n);
  }

  while (queue_1.Size() != 0 && queue_2.Size() != 0) {
    ++count;
    int x = queue_1.Front();
    int y = queue_2.Front();
    queue_1.Dequeue();
    queue_2.Dequeue();

    if (x == 0 && y == 9) {
      queue_1.Enqueue(x);
      queue_1.Enqueue(y);
    } else if (x == 9 && y == 0) {
      queue_2.Enqueue(x);
      queue_2.Enqueue(y);
    } else if (x > y) {
      queue_1.Enqueue(x);
      queue_1.Enqueue(y);
    } else {
      queue_2.Enqueue(x);
      queue_2.Enqueue(y);
    }

    if (queue_1.Size() == 0) {
      std::cout << "second"
                << " " << count;
      break;
    }

    if (queue_2.Size() == 0) {
      std::cout << "first"
                << " " << count;
      break;
    }

    if (count == 1000000) {
      std::cout << "botva";
      break;
    }
  }

  queue_1.Clear();
  queue_2.Clear();
  return 0;
}
