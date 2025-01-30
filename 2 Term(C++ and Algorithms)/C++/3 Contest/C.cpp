#ifndef ARRAY_TRAITS_H
#define ARRAY_TRAITS_H

#include <iostream>

template <class T>
struct kIsArray;

template <class T>
constexpr bool kIsArrayV = kIsArray<T>::value;

template <class T>
struct kIsArray<T[]> : std::true_type {};

template <class T, size_t N>
struct kIsArray<T[N]> : std::true_type {};

template <class T>
struct kIsArray : std::false_type {};

template <class T>
struct Rank;

template <class T>
constexpr size_t kRankV = Rank<T>::value;

template <class T>
struct Rank<T[]> : std::integral_constant<size_t, Rank<T>::value + 1> {};

template <class T, size_t N>
struct Rank<T[N]> : std::integral_constant<size_t, Rank<T>::value + 1> {};

template <class T>
struct Rank : std::integral_constant<size_t, 0> {};

template <class T>
struct RemoveArray;

template <class T>
using RemoveArrayT = typename RemoveArray<T>::Type;

template <class T, size_t N>
struct RemoveArray<T[N]> {
  using Type = T;
};

template <class T>
struct RemoveArray<T[]> {
  using Type = T;
};

template <class T>
struct RemoveArray {
  using Type = T;
};

template <class T>
struct Size;

template <class T>
constexpr size_t kSizeV = Size<T>::value;

template <class T>
struct Size<T[]> : std::integral_constant<size_t, 0> {};

template <class T, size_t N>
struct Size<T[N]> : std::integral_constant<size_t, N> {};

template <class T>
struct Size : std::integral_constant<size_t, sizeof(T) / sizeof(RemoveArrayT<T>)> {};

template <class T>
struct RemoveAllArrays;

template <class T>
using RemoveAllArraysT = typename RemoveAllArrays<T>::Type;

template <class T>
struct RemoveAllArrays<T[]> {
  using Type = typename RemoveAllArrays<RemoveArrayT<T>>::Type;
};

template <class T, size_t N>
struct RemoveAllArrays<T[N]> {
  using Type = typename RemoveAllArrays<RemoveArrayT<T>>::Type;
};

template <class T>
struct RemoveAllArrays {
  using Type = T;
};

template <class T>
struct TotalSize;

template <class T>
constexpr size_t kTotalSizeV = TotalSize<T>::value;

template <class T>
struct TotalSize<T[]> : std::integral_constant<size_t, 0> {};

template <class T>
struct TotalSize : std::integral_constant<size_t, sizeof(T) / sizeof(RemoveAllArraysT<T>)> {};
#endif
