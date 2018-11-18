#pragma once

#include "simple.hh"
#include <algorithm>

template <typename T>
static int _merge_inversions(std::vector<T> &A, int p, int q, int r) {
  int n1 = q - p + 1, n2 = r - q;
  std::vector<T> L(n1 + 1), R(n2 + 1);
  for (int i = 1; i <= n1; ++i)
    L[i - 1] = A[p + i - 2];
  for (int j = 1; j <= n2; ++j)
    R[j - 1] = A[q + j - 1];
  L[n1] = inf;
  R[n2] = inf;
  int i = 1, j = 1, inversions = 0, counted = 0;
  for (int k = p; k <= r; ++k) {
    if (!counted && R[j - 1] < L[i - 1]) {
      inversions += n1 - i + 1;
      counted = 1;
    }
    if (L[i - 1] <= R[j - 1]) {
      A[k - 1] = L[i - 1];
      ++i;
    } else {
      A[k - 1] = R[j - 1];
      ++j;
      counted = 0;
    }
  }
  return inversions;
}

template <typename T>
static int _count_inversions(std::vector<T> &A, int p, int r) {
  int count = 0;
  if (p < r) {
    int q = (p + r) / 2;
    count = _count_inversions(A, p, q) + _count_inversions(A, q + 1, r)
      + _merge_inversions(A, p, q, r);
  }
  return count;
}

template <typename T>
int count_inversions(std::vector<T> &A) {
  return _count_inversions(A, 1, A.size());
}

