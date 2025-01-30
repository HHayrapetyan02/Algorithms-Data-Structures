#ifndef ARRAY_H
#define ARRAY_H
#include <stdexcept>

class ArrayBig : public std::out_of_range {
 public:
  ArrayBig() : std::out_of_range("ArrayBig") {
  };  
};

template <typename T, size_t N>
class Array {
 public:
  T arr[N];

  const T& operator[](size_t i) const {
    return arr[i];
  }
  
  const T& Do(size_t i) const {
    if (i >= N) {
      throw ArrayBig{};
    }
    return arr[i];
  }

  T& Do(size_t i) {
    if (i >= N) {
      throw ArrayBig{};
    }
    return arr[i];
  }

  T& operator[](size_t i) {
    return arr[i];
  }

  const T& Front() const {
    return arr[0];
  }

  T& Front() {
    return arr[0];
  }

  const T& Back() const {
    return arr[N - 1];
  }

  T& Back() {
    return arr[N - 1];
  }

  const T* Data() const {
    return arr;
  }

  T* Data() {
    return arr;
  }

  size_t Size() const {
    return N;
  }

  bool Empty() const {
    return N == 0;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      arr[i] = value;
    }
  };
  
  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      std::swap(arr[i], other[i]);
    }
  };
};
#endif
