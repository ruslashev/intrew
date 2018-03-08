#pragma once
#include "util.hh"

size_t parent(size_t i) {
  return i / 2;
}

size_t left(size_t i) {
  return 2 * i;
}

size_t right(size_t i) {
  return 2 * i + 1;
}

template <typename T>
void max_heapify_rec(vector<T> &a, size_t heap_size, size_t i) {
  size_t l = left(i), r = right(i)
    , largest = (l < heap_size && a[l] > a[i]) ? l : i;
  if (r < heap_size && a[r] > a[largest])
    largest = r;
  if (largest != i) {
    std::swap(a[i], a[largest]);
    max_heapify_rec(a, heap_size, largest);
  }
}

template <typename T>
void max_heapify(vector<T> &a, size_t heap_size, size_t i) {
  while (i < heap_size) {
    size_t l = left(i), r = right(i)
      , largest = (l < heap_size && a[l] > a[i]) ? l : i;
    if (r < heap_size && a[r] > a[largest])
      largest = r;
    if (largest == i)
      break;
    std::swap(a[i], a[largest]);
    i = largest;
  }
}

template <typename T>
size_t build_max_heap(vector<T> &a) {
  size_t heap_size = a.size();
  for (int i = heap_size / 2; i >= 0; --i)
    max_heapify(a, heap_size, i);
  return heap_size;
}

template <typename T>
void heapsort(vector<T> &a) {
  size_t heap_size = build_max_heap(a);
  for (size_t i = a.size() - 1; i >= 1; --i) {
    std::swap(a[0], a[i]);
    --heap_size;
    max_heapify(a, heap_size, 0);
  }
}

// max-priority queue algorithms

template <typename T>
T heap_maximum(const vector<T> &a) {
  return a[0];
}

template <typename T>
T heap_extract_max(vector<T> &a, size_t &heap_size) {
  if (heap_size < 1)
    throw;
  T max = a[0];
  a[0] = a[heap_size - 1];
  --heap_size;
  max_heapify(a, 0);
  return max;
}

template <typename T>
void heap_increase_key(vector<T> &a, size_t i, T key) {
  if (key < a[i])
    throw;
  a[i] = key;
  while (i > 0 && a[parent(i)] < a[i]) {
    std::swap(a[i], a[parent(i)]);
    i = parent(i);
  }
}

template <typename T>
size_t max_heap_insert(vector<T> &a, size_t heap_size, T key) {
  ++heap_size;
  size_t i = heap_size - 1;
  a.push_back(key);
  while (i > 0 && a[parent(i)] < a[i]) {
    std::swap(a[i], a[parent(i)]);
    i = parent(i);
  }
  return heap_size;
}

