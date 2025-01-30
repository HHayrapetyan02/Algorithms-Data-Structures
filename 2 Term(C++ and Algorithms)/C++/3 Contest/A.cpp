#ifndef ITEROPS_H
#define ITEROPS_H

#include <iostream>
#include <iterator>
#include <type_traits>

template <typename Iterator, typename T>
constexpr void Advance(Iterator& iterator, T step) {
  using Category = typename std::iterator_traits<Iterator>::iterator_category;
  if constexpr (std::is_same_v<Category, std::random_access_iterator_tag>) {
    iterator += step;
  } else {
    typename std::iterator_traits<Iterator>::difference_type i = 0;
    for (i = 0; i < step; ++i) {
      ++iterator;
    }
    if constexpr (std::is_same_v<Category, std::bidirectional_iterator_tag>) {
      for (i = 0; i > step; --i) {
        --iterator;
      }
    }
  }
}

template <typename Iterator>
Iterator Next(Iterator iterator, typename std::iterator_traits<Iterator>::difference_type step = 1) {
  Advance(iterator, step);
  return iterator;
}

template <typename Iterator>
Iterator Prev(Iterator iterator, typename std::iterator_traits<Iterator>::difference_type step = 1) {
  Advance(iterator, -step);
  return iterator;
}

template <typename Iterator>
constexpr typename std::iterator_traits<Iterator>::difference_type Distance(Iterator first, Iterator second) {
  using Category = typename std::iterator_traits<Iterator>::iterator_category;

  if constexpr (std::is_base_of_v<std::random_access_iterator_tag, Category>) {
    return second - first;
  } else {
    typename std::iterator_traits<Iterator>::difference_type result = 0;
    while (first != second) {
      ++first;
      ++result;
    }
    return result;
  }
}

#endif
