#pragma once
#include "util.hh"

template <typename T>
bool binary_search(const vector<T> &a, T needle) {
  size_t beg = 0, end = a.size() - 1;
  while (beg <= end) {
    size_t mid = (beg + end) / 2;
    if (a[mid] < needle)
      end = mid - 1;
    else if (a[mid] > needle)
      beg = mid + 1;
    else
      return true;
  }
  return false;
}

