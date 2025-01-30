#ifndef HEAP_H
#define HEAP_H
#include <iostream>

template <class T>
void Swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <class T>
void SiftDown(T* begin, T* end, size_t i) {
  size_t left = 2 * i + 1;
  size_t right = 2 * i + 2;
  size_t largest = i;
  if ((begin + left) < end && *(begin + largest) < *(begin + left)) {
    largest = left;
  }
  if ((begin + right) < end && *(begin + largest) < *(begin + right)) {
    largest = right;
  }
  if (i < largest || largest < i) {
    Swap(*(begin + i), *(begin + largest));
    SiftDown(begin, end, largest);
  }
  return;
}

template <class T>
void SiftUp(T* begin, T* end, size_t i) {
  size_t parent = (i - 1) / 2;
  if (0 < i && *(begin + parent) < *(begin + i)) {
    Swap(*(begin + parent), *(begin + i));
    SiftUp(begin, end, parent);
  }
}

template <class T>
void PushHeap(T* begin, T* end) {
  size_t k = end - begin - 1;
  SiftUp(begin, end, k);
}

template <class T>
void PopHeap(T* begin, T* end) {
  size_t i = 0;
  Swap(*begin, *(end - 1));
  SiftDown(begin, end - 1, i);
}
#endif
