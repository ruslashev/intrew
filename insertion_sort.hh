#pragma once

#include "simple.hh"
#include "utils.hh"

template <typename T>
void insertion_sort(std::vector<T> *A) {
  for (int j = 2; j <= (int)A->size(); ++j) {
    const T key = (*A)[j - 1];
    int i = j - 1;
    while (i > 0 && (*A)[i - 1] > key) {
      (*A)[i] = (*A)[i - 1];
      --i;
    }
    (*A)[i] = key;
  }
}

