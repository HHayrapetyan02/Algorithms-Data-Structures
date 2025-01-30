#include <iostream>
#include <cstring>

struct Node {
  Node* prev = nullptr;
  Node* next = nullptr;
  int64_t value = 0;
};

class Dequeue {
  Node* first_ = nullptr;
  Node* last_ = nullptr;
  int dequeue_size_ = 0;

 public:
  void PushFront(int64_t k);
  void PushBack(int64_t k);
  void PopFront();
  void PopBack();
  void Front();
  void Back();
  void Pop();
  void Clear();
  void Exit();
  int Size();
};

int Dequeue::Size() {
  return this->dequeue_size_;
}

void Dequeue::Pop() {
  if (dequeue_size_ == 1) {
    delete this->first_;
    this->last_ = nullptr;
    this->first_ = nullptr;
    --(dequeue_size_);
    return;
  }
  Node* q = this->first_;
  this->first_ = this->first_->next;
  delete q;
  --(dequeue_size_);
}

void Dequeue::Clear() {
  if (Size() == 1) {
    Pop();
  }
  if (Size() > 1) {
    Pop();
    Clear();
  }
}

void Dequeue::Exit() {
  std::cout << "bye\n";
}

void Dequeue::Front() {
  if (this->dequeue_size_ == 0) {
    std::cout << "error\n";
    return;
  }
  std::cout << this->last_->value << "\n";
}

void Dequeue::Back() {
  if (this->dequeue_size_ == 0) {
    std::cout << "error\n";
    return;
  }
  std::cout << this->first_->value << "\n";
}

void Dequeue::PopBack() {
  if (dequeue_size_ == 0) {
    std::cout << "error\n";
    return;
  }
  if (dequeue_size_ == 1) {
    int64_t tmp = this->first_->value;
    delete this->first_;
    this->first_ = nullptr;
    this->last_ = nullptr;
    std::cout << tmp << "\n";
    --(dequeue_size_);
    return;
  }
  Node* q = this->first_;
  int64_t tmp = this->first_->value;
  this->first_ = this->first_->next;
  delete q;
  --(dequeue_size_);
  std::cout << tmp << "\n";
}

void Dequeue::PopFront() {
  if (dequeue_size_ == 0) {
    std::cout << "error\n";
    return;
  }
  if (dequeue_size_ == 1) {
    int64_t tmp = this->last_->value;
    delete this->last_;
    this->first_ = nullptr;
    this->last_ = nullptr;
    std::cout << tmp << "\n";
    --(dequeue_size_);
    return;
  }
  Node* q = this->last_;
  int64_t tmp = this->last_->value;
  this->last_ = this->last_->prev;
  delete q;
  --(dequeue_size_);
  std::cout << tmp << "\n";
}

void Dequeue::PushFront(int64_t k) {
  Node* q = new Node;
  q->value = k;
  q->prev = this->last_;
  q->next = nullptr;
  if (this->last_) {
    this->last_->next = q;
  }
  if (!this->first_) {
    this->first_ = q;
  }
  this->last_ = q;
  ++(dequeue_size_);
  std::cout << "ok\n";
}

void Dequeue::PushBack(int64_t k) {
  Node* q = new Node;
  q->value = k;
  q->next = this->first_;
  q->prev = nullptr;
  if (this->first_) {
    this->first_->prev = q;
  }
  if (!this->last_) {
    this->last_ = q;
  }
  this->first_ = q;
  ++(dequeue_size_);
  std::cout << "ok\n";
}

int main() {
  Dequeue dequeue;
  int k = 0;
  std::cin >> k;
  auto command = new char[20]{};

  for (int i = 0; i < k; ++i) {
    scanf("%s", command);
    if (std::strcmp(command, "push_front") == 0) {
      int64_t tmp = 0;
      std::cin >> tmp;
      dequeue.PushFront(tmp);
    } else if (std::strcmp(command, "push_back") == 0) {
      int64_t tmp = 0;
      std::cin >> tmp;
      dequeue.PushBack(tmp);
    } else if (std::strcmp(command, "pop_back") == 0) {
      dequeue.PopBack();
    } else if (std::strcmp(command, "pop_front") == 0) {
      dequeue.PopFront();
    } else if (std::strcmp(command, "front") == 0) {
      dequeue.Front();
    } else if (std::strcmp(command, "back") == 0) {
      dequeue.Back();
    } else if (std::strcmp(command, "size") == 0) {
      std::cout << dequeue.Size() << "\n";
    } else if (std::strcmp(command, "clear") == 0) {
      dequeue.Clear();
      std::cout << "ok\n";
    }
    if (std::strcmp(command, "exit") == 0) {
      dequeue.Exit();
    }
  }
  delete[] command;
  dequeue.Clear();
  return 0;
}
