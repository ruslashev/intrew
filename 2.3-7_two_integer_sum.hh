#pragma once
#include "util.hh"
#include "2.3.1_merge_sort.hh"
#include "2.3-5_binary_search.hh"

// doesn't really work, because for array [1..10] and x = 2 returns true
template <typename T>
bool sum_exists(vector<T> a, int x) {
  merge_sort(a);
  for (size_t i = 0; i < a.size(); ++i)
    if (binary_search(a, x - a[i])) {
      return true;
    }
  return false;
}

template <typename T>
bool sum_exists_better(vector<T> a, int x) {
  map<int, int> seen;
  for (size_t i = 0; i < a.size(); ++i) {
    if (seen.count(x - a[i]) > 0)
      return true;
    seen[a[i]] = 1337;
  }
  return false;
}

