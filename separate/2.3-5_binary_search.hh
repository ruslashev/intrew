#pragma once
#include "util.hh"

template <typename T>
bool binary_search(const vector<T> &a, T needle) {
  int beg = 0, end = a.size() - 1;
  while (beg <= end) {
    int mid = (beg + end) / 2;
    if (needle < a[mid])
      end = mid - 1;
    else if (needle > a[mid])
      beg = mid + 1;
    else
      return true;
  }
  return false;
}

