#pragma once

#include "simple.hh"

static size_t _left(size_t i) {
  return 2 * i;
}

static size_t _right(size_t i) {
  return 2 * i + 1;
}

template <typename T>
static void _max_heapify(std::vector<T> *A, size_t heap_size, size_t i) {
  while (i < heap_size) {
    size_t l = _left(i), r = _right(i), largest;
    largest = (l <= heap_size && (*A)[l - 1] > (*A)[i - 1]) ? l : i;
    if (r <= heap_size && (*A)[r - 1] > (*A)[largest - 1])
      largest = r;
    if (largest != i) {
      std::swap((*A)[i - 1], (*A)[largest - 1]);
      i = largest;
    } else
      break;
  }
}

template <typename T>
static void _build_max_heap(std::vector<T> *A, size_t &heap_size) {
  heap_size = A->size();
  for (size_t i = heap_size / 2; i >= 1; --i)
    _max_heapify(A, heap_size, i);
}

template <typename T>
void heapsort(std::vector<T> *A) {
  size_t heap_size;
  _build_max_heap(A, heap_size);
  for (size_t i = A->size(); i >= 2; --i) {
    std::swap((*A)[0], (*A)[i - 1]);
    --heap_size;
    _max_heapify(A, heap_size, 1);
  }
}

