#ifndef ISPRIME_H
#define ISPRIME_H

#include <iostream>
#include <type_traits>

template <size_t N, size_t L, size_t R, bool Prime>
struct HelperSqrt;

template <size_t N>
constexpr size_t kSqrtV = HelperSqrt<N, 0, N, ((N / 2 + 1) > N / (N / 2 + 1))>::value;

template <size_t N, size_t L, size_t R>
struct HelperSqrt<N, L, R, false>
    : std::integral_constant<
          size_t, HelperSqrt<N, (L + R) / 2 + 1, R, (((3 * R + L + 6) / 4) > N / ((3 * R + L + 6) / 4))>::value> {};

template <size_t N, size_t L, size_t R>
struct HelperSqrt<N, L, R, true>
    : std::integral_constant<
          size_t, HelperSqrt<N, L, (L + R) / 2, (((3 * L + R + 4) / 4) > N / ((3 * L + R + 4) / 4))>::value> {};

template <size_t N, size_t R>
struct HelperSqrt<N, R, R, true> : std::integral_constant<size_t, R> {};

template <size_t N, size_t R>
struct HelperSqrt<N, R, R, false> : std::integral_constant<size_t, R> {};

template <size_t N, size_t L, size_t R, bool Prime>
struct HasDivisorOn;

template <size_t N, size_t L, size_t R>
constexpr bool kHasDivisorOnV = HasDivisorOn<N, L, R, (L < R)>::value;

template <size_t N, size_t L, size_t R>
struct HasDivisorOn<N, L, R, true>
    : std::integral_constant<bool,
                             std::disjunction<HasDivisorOn<N, L, (L + R) / 2, (L < (L + R) / 2)>,
                                              HasDivisorOn<N, (L + R) / 2 + 1, R, ((L + R) / 2 + 1 < R)>>::value> {};

template <size_t N, size_t L, size_t R>
struct HasDivisorOn<N, L, R, false> : std::true_type {};

template <size_t N, size_t M>
struct HasDivisorOn<N, M, M, false> : std::integral_constant<bool, (N % M == 0)> {};

template <size_t N>
constexpr bool kIsPrimeV = !kHasDivisorOnV<N, 2, kSqrtV<N>> || (N == 2 || N == 3);
#endif
