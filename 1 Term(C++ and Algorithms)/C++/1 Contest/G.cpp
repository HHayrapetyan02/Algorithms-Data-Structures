#ifndef MERGE_H
#define MERGE_H
template <class T, class U, class K>
void Merge(const T* first_begin, const T* first_end, const U* second_begin, const U* second_end, K* out) {
  int n = first_end - first_begin;
  int m = second_end - second_begin;
  int index_1 = 0;
  int index_2 = 0;
  int index_finish = 0;
  while (index_1 < n && index_2 < m) {
    if (first_begin[index_1] < second_begin[index_2]) {
      out[index_finish] = first_begin[index_1];
      ++index_1;
      ++index_finish;
    } else {
      out[index_finish] = second_begin[index_2];
      ++index_2;
      ++index_finish;
    }
  }
  while (index_1 < n) {
    out[index_finish] = first_begin[index_1];
    ++index_1;
    ++index_finish;
  }

  while (index_2 < m) {
    out[index_finish] = second_begin[index_2];
    ++index_2;
    ++index_finish;
  }
}
#endif
