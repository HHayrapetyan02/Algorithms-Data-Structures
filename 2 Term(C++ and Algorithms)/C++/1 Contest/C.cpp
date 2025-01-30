#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <stdexcept>
#include <iostream>

template <class T>
class SharedPtr {
  T* ptr_;
  int* strong_counter_;

 public:
  SharedPtr() noexcept;
  SharedPtr(T*) noexcept;  // NOLINT
  SharedPtr& operator=(const SharedPtr&);
  SharedPtr(const SharedPtr&) noexcept;
  SharedPtr& operator=(SharedPtr&&) noexcept;
  SharedPtr(SharedPtr&&) noexcept;
  ~SharedPtr();
  void Reset(T* ptr = nullptr);
  void Swap(SharedPtr<T>&);
  T* Get() const;
  int UseCount() const;
  T& operator*() const;
  T* operator->() const;
  explicit operator bool() const;
};

template <class T>
SharedPtr<T>::SharedPtr() noexcept : ptr_(nullptr), strong_counter_(nullptr) {
}

template <class T>
SharedPtr<T>::SharedPtr(T* ptr) noexcept : ptr_(ptr) {
  if (ptr_ == nullptr) {
    strong_counter_ = nullptr;
  } else {
    strong_counter_ = new int(1);
  }
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
  if (this != &other) {
    if (strong_counter_ != nullptr) {
      if (*strong_counter_ == 1) {
        delete ptr_;
        delete strong_counter_;
      } else {
        --*strong_counter_;
      }
    }
    ptr_ = other.ptr_;
    if (other.strong_counter_ != nullptr) {
      ++*other.strong_counter_;
    }
    strong_counter_ = other.strong_counter_;
  }
  return *this;
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) noexcept : ptr_(other.ptr_) {
  if (other.strong_counter_ == nullptr) {
    strong_counter_ = nullptr;
  } else {
    ++*other.strong_counter_;
    strong_counter_ = other.strong_counter_;
  }
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {
  if (this != &other) {
    if (strong_counter_ != nullptr) {
      if (*strong_counter_ == 1) {
        delete ptr_;
        delete strong_counter_;
      } else {
        --*strong_counter_;
      }
    }
    ptr_ = other.ptr_;
    strong_counter_ = other.strong_counter_;
    other.ptr_ = nullptr;
    other.strong_counter_ = nullptr;
  }
  return *this;
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), strong_counter_(other.strong_counter_) {
  other.ptr_ = nullptr;
  other.strong_counter_ = nullptr;
}

template <class T>
SharedPtr<T>::~SharedPtr() {
  if (strong_counter_ != nullptr) {
    --*strong_counter_;
    if (*strong_counter_ == 0) {
      delete ptr_;
      delete strong_counter_;
    }
  }
}

template <class T>
void SharedPtr<T>::Reset(T* ptr) {
  this->~SharedPtr();
  ptr_ = ptr;
  if (ptr_ == nullptr) {
    strong_counter_ = nullptr;
  } else {
    strong_counter_ = new int(1);
  }
}

template <class T>
void SharedPtr<T>::Swap(SharedPtr<T>& other) {
  std::swap(ptr_, other.ptr_);
  std::swap(strong_counter_, other.strong_counter_);
}

template <class T>
T* SharedPtr<T>::Get() const {
  return ptr_;
}

template <class T>
int SharedPtr<T>::UseCount() const {
  return ptr_ == nullptr ? 0 : *strong_counter_;
}

template <class T>
T& SharedPtr<T>::operator*() const {
  return *ptr_;
}

template <class T>
T* SharedPtr<T>::operator->() const {
  return ptr_;
}

template <class T>
SharedPtr<T>::operator bool() const {
  return ptr_;
}
#endif
