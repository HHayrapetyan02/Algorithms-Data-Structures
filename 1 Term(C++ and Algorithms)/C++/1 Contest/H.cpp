#ifndef STATIC_H
#define STATIC_H
template <class T>
void Swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <class T>
T* Partition(T* begin, T* end) {
  T p_value = *(begin + (end - begin) / 2);
  T* left = begin;
  T* right = end;
  while (left <= right) {
    while (*left < p_value) {
      ++left;
    }
    while (p_value < *right) {
      --right;
    }
    if (right < left) {
      break;
    }
    Swap(*left, *right);
    ++left;
    --right;
  }
  return right;
}

template <class T>
void KthElement(T* begin, T* k, T* end) {
  T* left = begin;
  T* right = end - 1;
  while (left < right - 1) {
    T* mid = Partition(left, right);
    if (mid == k) {
      return;
    } else if (k < mid) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
}
#endif
