#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stack>
#include <deque>

template<class T, class Container = std::deque<T>>
class Stack {
  Container container_;

 public:
  Stack();
  explicit Stack(const Container&);
  template<class Iterator>
  Stack(const Iterator&, const Iterator&);
  T& Top();
  const T& Top() const;
  bool Empty() const;
  size_t Size() const;
  void Push(const T&);
  void Push(T&&);
  template<class...Args>
  void Emplace(Args&&...);
  void Pop();
  void Swap(Stack&);  
};

template<class T, class Container>
Stack<T, Container>::Stack() = default;

template<class T, class Container>
Stack<T, Container>::Stack(const Container& container) : container_(container) {
}

template<class T, class Container>
template<class Iterator>
Stack<T, Container>::Stack(const Iterator& first, const Iterator& second) : container_(first, second) {
}

template<class T, class Container>
T& Stack<T, Container>::Top() {
  return container_.back();
}

template<class T, class Container>
const T& Stack<T, Container>::Top() const {
  return container_.back();
}

template<class T, class Container>
bool Stack<T, Container>::Empty() const {
  return container_.empty();
}

template<class T, class Container>
size_t Stack<T, Container>::Size() const {
  return container_.size();
}

template<class T, class Container>
void Stack<T, Container>::Push(const T& value) {
  container_.emplace_back(value);
}

template<class T, class Container>
void Stack<T, Container>::Push(T&& value) {
  container_.emplace_back(std::move(value));
}

template<class T, class Container>
template<class... Args>
void Stack<T, Container>::Emplace(Args&&... args) {
  container_.emplace_back(std::forward<Args>(args)...);
}

template<class T, class Container>
void Stack<T, Container>::Pop() {
  container_.pop_back();
}

template<class T, class Container>
void Stack<T, Container>::Swap(Stack& other) {
  container_.swap(other.container_);
}

#endif
