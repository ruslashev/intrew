#pragma once

#include "simple.hh"

template <typename T>
static size_t _partition_lomuto(std::vector<T> *A, size_t p, size_t r) {
  size_t i = p;
  for (size_t j = p; j <= r - 1; ++j)
    if ((*A)[j - 1] <= (*A)[r - 1])
      std::swap((*A)[i++ - 1], (*A)[j - 1]);
  std::swap((*A)[i - 1], (*A)[r - 1]);
  return i;
}

template <typename T>
static void _quicksort_lomuto(std::vector<T> *A, size_t p, size_t r) {
  if (p < r) {
    size_t q = _partition_lomuto(A, p, r);
    _quicksort_lomuto(A, p, q - 1);
    _quicksort_lomuto(A, q + 1, r);
  }
}

template <typename T>
void quicksort_lomuto(std::vector<T> *A) {
  _quicksort_lomuto(A, 1, A->size());
}

template <typename T>
static size_t _partition_hoare(std::vector<T> *A, size_t p, size_t r) {
  size_t i = p - 1, j = r + 1;
  while (1) {
    do {
      --j;
    } while (!((*A)[j - 1] <= (*A)[p - 1]));
    do {
      i++;
    } while (!((*A)[i - 1] >= (*A)[p - 1]));
    if (i < j)
      std::swap((*A)[i - 1], (*A)[j - 1]);
    else
      return j;
  }
}

template <typename T>
static void _quicksort_hoare(std::vector<T> *A, size_t p, size_t r) {
  if (p < r) {
    size_t q = _partition_hoare(A, p, r);
    _quicksort_hoare(A, p, q);
    _quicksort_hoare(A, q + 1, r);
  }
}

template <typename T>
void quicksort_hoare(std::vector<T> *A) {
  _quicksort_hoare(A, 1, A->size());
}

template <typename T>
void quicksort(std::vector<T> *A) {
  return quicksort_hoare(A);
}

