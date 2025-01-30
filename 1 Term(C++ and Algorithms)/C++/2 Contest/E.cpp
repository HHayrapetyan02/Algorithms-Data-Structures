#ifndef HEAP_H
#define HEAP_H

template <class T>
void Swap(T& x, T& y){
  T tmp = x;
  x = y;
  y = tmp;
}

template <class T>
void SiftDown(T* begin, T* end, int i) {
  int n = end - begin;
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && (*(begin + largest) < *(begin + left))) {
    largest = left;
  }

  if (right < n && (*(begin + largest) < *(begin + right))) {
    largest = right;
  }

  if (largest != i) {
    Swap(*(begin + i), *(begin + largest));
    SiftDown(begin, end, largest);
  }
}

template <class T>
void MakeHeap(T* begin, T* end) {
  int n = end - begin;
  for (int i = n / 2; i >= 0; --i) {
    SiftDown(begin, end, i);
  }
}

template <class T>
void SortHeap(T* begin, T* end) {
  MakeHeap(begin, end);
  int n = end - begin;
  for (int i = n - 1; i >= 0; --i) {
    Swap(*begin, *(begin + i));
    --n;
    end = begin + n;
    SiftDown(begin, end, 0);
  }
}
#endif
