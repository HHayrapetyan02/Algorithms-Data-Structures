#ifndef UNIQUEPTR_H
#define UNIQUEPTR_H

template <class T>
class UniquePtr {
  T* ptr_;

 public:
  UniquePtr() noexcept;
  explicit UniquePtr(T*) noexcept;
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&&) noexcept;
  UniquePtr& operator=(UniquePtr&&) noexcept;
  ~UniquePtr();
  T* Release();
  void Reset(T* ptr = nullptr);
  void Swap(UniquePtr&) noexcept;
  T* Get() const;
  T& operator*() const;
  T* operator->() const;
  explicit operator bool() const;
};

template <class T>
UniquePtr<T>::UniquePtr() noexcept : ptr_(nullptr) {
}

template <class T>
UniquePtr<T>::UniquePtr(T* pointer) noexcept : ptr_(pointer) {
}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept : ptr_(other.ptr_) {
  other.ptr_ = nullptr;
}

template <class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept {
  if (this != &other) {
    delete ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }
  return *this;
}

template <class T>
UniquePtr<T>::~UniquePtr() {
  delete ptr_;
}

template <class T>
T* UniquePtr<T>::Release() {
  T* tmp = ptr_;
  ptr_ = nullptr;
  return tmp;
}

template <class T>
void UniquePtr<T>::Reset(T* ptr) {
  delete ptr_;
  ptr_ = ptr;
}

template <class T>
void UniquePtr<T>::Swap(UniquePtr<T>& other) noexcept {
  T* tmp = std::move(other.ptr_);
  other.ptr_ = std::move(ptr_);
  ptr_ = std::move(tmp);
}

template <class T>
T* UniquePtr<T>::Get() const {
  return ptr_;
}

template <class T>
T& UniquePtr<T>::operator*() const {
  return *ptr_;
}

template <class T>
T* UniquePtr<T>::operator->() const {
  return ptr_;
}

template <class T>
UniquePtr<T>::operator bool() const {
  return ptr_;
}
#endif
