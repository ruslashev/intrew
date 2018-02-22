#pragma once

#include "util.hh"

template <typename T>
static void merge(vector<T> &a, int beg, int mid, int end) {
  vector<T> left(mid - beg + 1), right(end - mid);
  for (size_t i = 0; i < left.size(); ++i)
    left[i] = a[beg + i];
  for (size_t j = 0; j < right.size(); ++j)
    right[j] = a[mid + j + 1];
  left.push_back(inf);
  right.push_back(inf);
  for (int i = 0, j = 0, k = beg; k <= end; ++k)
    if (left[i] <= right[j])
      a[k] = left[i++];
    else
      a[k] = right[j++];
}

template <typename T>
static void merge_sort(vector<T> &a, int beg, int end) {
  // if (end - beg > 0) {
  if (beg < end) {
    int mid = (beg + end) / 2;
    merge_sort(a, beg, mid);
    merge_sort(a, mid + 1, end);
    merge(a, beg, mid, end);
  }
}

template <typename T>
void merge_sort(vector<T> &a) {
  merge_sort(a, 0, a.size() - 1);
}

