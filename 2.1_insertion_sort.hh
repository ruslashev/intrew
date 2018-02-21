#pragma once

#include "util.hh"

template <typename T>
void insertion_sort(vector<T> &A) {
  for (size_t i = 1; i < A.size(); ++i) {
    const T key = A[i];
    size_t j = i - 1;
    for (; j >= 0 && A[j] > key; --j)
      A[j + 1] = A[j];
    A[j + 1] = key;
  }
}

