#pragma once

#include "simple.hh"
#include "utils.hh"

template <typename T>
void radix_sort(std::vector<T> &A) {
  const T max = vector_max(A);

  std::vector<T> B(A.size());
  int C[10];

  for (int d = 1; max / d > 0; d *= 10) {
    C[0] = C[1] = C[2] = C[3] = C[4] = C[5] = C[6] = C[7] = C[8] = C[9] = 0;
    for (size_t i = 0; i < A.size(); i++)
      C[(A[i] / d) % 10]++;
    for (int i = 1; i < 10; i++)
      C[i] += C[i - 1];
    for (int i = A.size() - 1; i >= 0; i--) {
      T x = (A[i] / d) % 10;
      B[C[x] - 1] = A[i];
      C[x]--;
    }
    A = B;
  }
}

