#ifndef SORT_H
#define SORT_H
template <class T>
void Merge(T* first_begin, T* first_end, T* second_begin, T* second_end, T* out) {
  int n = first_end - first_begin;
  int m = second_end - second_begin;
  int i = 0;
  int j = 0;
  int k = 0;
  while (i < n && j < m) {
    if (first_begin[i] < second_begin[j]) {
      out[k] = first_begin[i];
      ++i;
    } else {
      out[k] = second_begin[j];
      ++j;
    }
    ++k;
  }
  while (i < n) {
    out[k] = first_begin[i];
    ++i;
    ++k;
  }
  while (j < m) {
    out[k] = second_begin[j];
    ++j;
    ++k;
  }
}

template <class T>
void Sort(T* begin, T* end) {
  if (end - begin < 2) {
    return;
  }
  T* mid = begin + (end - begin) / 2;
  Sort(begin, mid);
  Sort(mid, end);
  auto new_arr = new T[end - begin]{};
  Merge(begin, mid, mid, end, new_arr);
  for (int i = 0; i < end - begin; ++i) {
    begin[i] = new_arr[i];
  }
  delete[] new_arr;
}
#endif
