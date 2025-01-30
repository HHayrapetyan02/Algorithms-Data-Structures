#ifndef BINARY
#define BINARY
template <class T>
bool BinarySearch(const T* begin, const T* end, const T& value) {
  const T* left = begin - 1;
  const T* right = end;
  while (left < right - 1) {
    const T* mid = left + (right - left) / 2;
    if (*mid < value) {
      left = mid;
    } else {
      right = mid;
    }
  }
  if (*(end - 1) < value) {
    return false;
  }
  return !(*right < value) && (!(value < *right));
}

template <class T>
const T* LowerBound(const T* begin, const T* end, const T& value) {
  const T* left = begin - 1;
  const T* right = end;
  while (left < right - 1) {
    const T* mid = left + (right - left) / 2;
    if (*mid < value) {
      left = mid;
    } else {
      right = mid;
    }
  }
  if (*(end - 1) < value) {
    return end;
  }
  return right;
}

template <class T>
const T* UpperBound(const T* begin, const T* end, const T& value) {
  const T* left = begin - 1;
  const T* right = end;
  while (left < right - 1) {
    const T* mid = left + (right - left) / 2;
    if (!(value < *mid)) {
      left = mid;
    } else {
      right = mid;
    }
  }
  if (!(value < *(end - 1))) {
    return end;
  }
  return right;
}
#endif
