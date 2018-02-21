#pragma once

#include "simple.hh"
#include "utils.hh"

template <typename T>
static std::vector<int>
_preprocess_count_integers_in_range(const std::vector<T> &A, int k) {
  std::vector<int> C(k + 1, 0);
  for (size_t i = 0; i < A.size(); ++i)
    ++C[A[i]];
  for (int i = 0; i < k; ++i)
    C[i] += C[i - 1];
  return C;
}

template <typename T>
int count_integers_in_range(const std::vector<T> &A, T a, T b) {
  std::vector<int> C = _preprocess_count_integers_in_range(A, vector_max(A));
  return C[b - 1] - C[a - 1];
}

