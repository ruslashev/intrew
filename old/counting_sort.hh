#pragma once

#include "simple.hh"
#include "utils.hh"

template <typename T>
static void _counting_sort(std::vector<T> &A, int k) {
  std::vector<T> output(A.size());
  std::vector<int> C(k + 1, 0);
  for (size_t i = 0; i < A.size(); ++i)
    ++C[A[i] - 1];
  for (int i = 0; i < k; ++i)
    C[i] += C[i - 1];
  for (size_t i = A.size(); i >= 1; --i) {
    output[C[A[i - 1] - 1] - 1] = A[i - 1];
    --C[A[i - 1] - 1];
  }
  A = output;
}

template <typename T>
void counting_sort(std::vector<T> &A) {
  _counting_sort(A, vector_max(A));
}

