#pragma once

#include "util.hh"

template <typename T>
void counting_sort(std::vector<T> &a, int k) {
  std::vector<T> output(a.size());
  std::vector<int> c(k + 1, 0);
  for (size_t i = 0; i < a.size(); ++i)
    ++c[a[i]];
  for (int i = 1; i <= k; ++i)
    c[i] += c[i - 1];
  for (int i = a.size() - 1; i >= 0; --i) {
    output[c[a[i]] - 1] = a[i];
    --c[a[i]];
  }
  a = output;
}

template <typename T>
void counting_sort(std::vector<T> &a) {
  counting_sort(a, vector_max(a));
}

