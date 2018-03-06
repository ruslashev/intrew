#pragma once
#include "util.hh"

size_t _left(size_t i) {
  return 2 * i;
}

size_t _right(size_t i) {
  return 2 * i + 1;
}

template <typename T>
void max_heapify(vector<T> &a, size_t heap_size, size_t i) {
  while (i < heap_size) {
    size_t l = _left(i), r = _right(i)
      , largest = (l <= heap_size && a[l - 1] > a[i - 1]) ? l : i;
    if (r <= heap_size && a[r - 1] > a[largest - 1])
      largest = r;
    if (largest != i) {
      std::swap(a[i - 1], a[largest - 1]);
      i = largest;
    } else
      break;
  }
}

template <typename T>
size_t build_max_heap(vector<T> &a) {
  size_t heap_size = a.size();
  for (size_t i = heap_size / 2; i >= 1; --i)
    max_heapify(a, heap_size, i);
  return heap_size;
}

template <typename T>
void heapsort(vector<T> &a) {
  size_t heap_size = build_max_heap(a, heap_size);
  for (size_t i = a.size(); i >= 2; --i) {
    std::swap(a[0], a[i - 1]);
    --heap_size;
    max_heapify(a, heap_size, 1);
  }
}

