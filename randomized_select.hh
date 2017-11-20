#pragma once

#include "simple.hh"
#include "utils.hh"

// Randomized select

template <typename T>
static size_t _partition_rec(std::vector<T> &A, size_t p, size_t r) {
  size_t i = p - 1;
  for (size_t j = p; j <= r - 1; ++j)
    if (A[j] <= A[r]) {
      ++i;
      std::swap(A[i], A[j]);
    }
  std::swap(A[i + 1], A[r]);
  return i + 1;
}

template <typename T>
static size_t _randomized_partition_rec(std::vector<T> &A, size_t p, size_t r) {
  size_t i = rand_in_range(p, r);
  std::swap(A[i], A[r]);
  return _partition_rec(A, p, r);
}

template <typename T>
static int _randomized_select_rec(std::vector<T> A, size_t p, size_t r, size_t i) {
  if (p == r)
    return A[p];
  size_t q = _randomized_partition(A, p, r);
  size_t k = q - p + 1;
  if (i == k)
    return A[q];
  else if (i < k)
    return _randomized_select_rec(A, p, q - 1, i);
  else
    return _randomized_select_rec(A, q + 1, r, i - k);
}

template <typename T>
int randomized_select_rec(std::vector<T> A, size_t i) {
  return _randomized_select_rec(A, 1, A.length, i);
}

// Iterative randomized select

template <typename T>
static size_t _partition_it(std::vector<T> &A, size_t p, size_t r) {
  size_t i = p;
  for (size_t j = p; j <= r - 1; ++j)
    if (A[j] <= A[r])
      std::swap(A[i++], A[j]);
  std::swap(A[i], A[r]);
  return i;
}

template <typename T>
static size_t _randomized_partition_it(std::vector<T> &A, size_t p, size_t r) {
  size_t i = rand_in_range(p, r);
  std::swap(A[i], A[r]);
  return _partition_it(A, p, r);
}

template <typename T>
static int _randomized_select_it(std::vector<T> A, size_t p, size_t r, size_t i) {
  while (p < r) {
    size_t q = _randomized_partition_it(A, p, r);
    size_t k = q - p + 1;
    if (i == k)
      return A[q];
    else if (i < k)
      r = q - 1;
    else {
      p = q + 1;
      i = i - k;
    }
  }
  return A[p];
}

template <typename T>
int randomized_select_it(std::vector<T> A, size_t i) {
  return randomized_select_it(A, 1, A.length, i);
}

