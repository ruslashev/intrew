#pragma once

#include "simple.hh"

// warning: uses 'inf' even though vector elements are templated
template <typename T>
static void _merge_unused(std::vector<T> *A, int p, int q, int r) {
  int n1 = q - p + 1, n2 = r - q;
  std::vector<T> L(n1 + 1), R(n2 + 1);
  for (int i = 1; i <= n1; ++i)
    L[i - 1] = (*A)[p + i - 2];
  for (int j = 1; j <= n2; ++j)
    R[j - 1] = (*A)[q + j - 1];
  L[n1] = inf;
  R[n2] = inf;
  int i = 1, j = 1;
  for (int k = p; k <= r; ++k)
    if (L[i - 1] <= R[j - 1]) {
      (*A)[k - 1] = L[i - 1];
      ++i;
    } else {
      (*A)[k - 1] = R[j - 1];
      ++j;
    }
}

template <typename T>
static void _merge(std::vector<T> *A, int p, int q, int r) {
  int n1 = q - p + 1, n2 = r - q;
  std::vector<T> L(n1), R(n2);
  for (int i = 1; i <= n1; ++i)
    L[i - 1] = (*A)[p + i - 2];
  for (int j = 1; j <= n2; ++j)
    R[j - 1] = (*A)[q + j - 1];
  int i = 1, j = 1, k = p;
  while (i <= n1 && j <= n2) {
    if (L[i - 1] <= R[j - 1]) {
      (*A)[k - 1] = L[i - 1];
      ++i;
    } else {
      (*A)[k - 1] = R[j - 1];
      ++j;
    }
    ++k;
  }
  while (i != n1 + 1)
    (*A)[k++ - 1] = L[i++ - 1];
  while (j != n2 + 1)
    (*A)[k++ - 1] = R[j++ - 1];
}

template <typename T>
static void _merge_sort(std::vector<T> *A, int p, int r) {
  if (p < r) {
    int q = (p + r) / 2;
    _merge_sort(A, p, q);
    _merge_sort(A, q + 1, r);
    _merge(A, p, q, r);
  }
}

template <typename T>
void merge_sort(std::vector<T> *A) {
  _merge_sort(A, 1, A->size());
}

