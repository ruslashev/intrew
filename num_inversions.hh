#pragma once

#include "simple.hh"
#include <algorithm>

template <typename T>
static int count_inversions(std::vector<T> &A, int p, int q, int r) {
  int n1 = q - p + 1, n2 = r - q;
  std::vector<T> L(n1), R(n2);
  for (int i = 1; i <= n1; ++i)
    L[i - 1] = A[p + i - 2];
  for (int j = 1; j <= n2; ++j)
    R[j - 1] = A[q + j - 1];
  int i = 1, j = 1, k = p, inversions = 0;
  while (i <= n1 && j <= n2) {
    if (L[i - 1] <= R[j - 1]) {
      A[k - 1] = L[i - 1];
      ++i;
    } else {
      A[k - 1] = R[j - 1];
      ++j;
      inversions += n1 - i + 1;
    }
    ++k;
  }
  while (j != n2 + 1) {
    A[k++ - 1] = R[j++ - 1];
    inversions += n1 - i + 1;
  }
  while (i != n1 + 1)
    A[k++ - 1] = L[i++ - 1];
  return inversions;
}

template <typename T>
static int num_inversions(std::vector<T> &A, int p, int r) {
  int count = 0;
  if (p < r) {
    int q = (p + r) / 2;
    count = num_inversions(A, p, q) + num_inversions(A, q + 1, r)
      + count_inversions(A, p, q, r);
  }
  return count;
}

template <typename T>
int num_inversions(std::vector<T> &A) {
  return num_inversions(A, 1, A.size());
}

