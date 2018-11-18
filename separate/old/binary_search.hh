#pragma once

#include "simple.hh"

template <typename T>
void binary_search(const std::vector<T> &A, const T& needle, bool *found
    , int *idx) {
  int p = 1, r = A.size();
  while (p <= r) {
    int q = (p + r) / 2;
    if (needle == A[q - 1]) {
      *found = true;
      *idx = q;
      return;
    } if (needle > A[q - 1])
      p = q + 1;
    else
      r = q - 1;
  }
  *found = false;
}

