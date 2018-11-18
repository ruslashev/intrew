#pragma once

#include "simple.hh"

template <typename T>
static T _median5(std::vector<T> &A, size_t p, size_t r) {
  for (size_t j = p; j <= r; ++j) {
    T key = A[j - 1];
    size_t i = j - 1;
    while (i >= p && key < A[i - 1]) {
      A[i] = A[i - 1];
      --i;
    }
    A[i] = key;
  }
  size_t n = r - p + 1;
  return n % 2 == 0 ? A[p + n / 2 - 2] : A[p + n / 2 - 1];
}

template <typename T>
static T _select(std::vector<T> &A, size_t p, size_t r, size_t i) {
  size_t n = r - p + 1, j;
  std::vector<T> medians((n + 4) / 5);
  for (j = 1; j <= n / 5; ++j)
    medians[j - 1] = _median5(A, p + (j - 1) * 5, p + (j - 1) * 5 + 4);
  if (n % 5 != 0)
    medians[j - 1] = _median5(A, p + (j - 1) * 5, p + (j - 1) * 5 + n % 5 - 1);

  T x = medians.size() == 1 ? medians[0]
    : _select(medians, 1, medians.size(), medians.size() / 2);

  size_t k = 0;
  for (size_t j = p, l = p; j <= r; ++j)
    if (A[j - 1] <= x) {
      std::swap(A[l++ - 1], A[j - 1]);
      ++k;
    }

  if (i == k)
    return x;
  else if (i < k)
    return _select(A, p, p + k - 1, i);
  else
    return _select(A, p + k, r, i - k);
}

template <typename T>
T select(std::vector<T> A, size_t i) {
  return _select(A, 1, A.size(), i);
}

