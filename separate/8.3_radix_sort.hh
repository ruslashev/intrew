#pragma once
#include "util.hh"

template <typename T>
void radix_sort(std::vector<T> &a) {
  const T max = vector_max(a);

  std::vector<T> b(a.size());
  int c[10];

  for (int d = 1; max / d > 0; d *= 10) {
    for (size_t i = 0; i < 10; ++i)
      c[i] = 0;
    for (size_t i = 0; i < a.size(); i++)
      c[(a[i] / d) % 10]++;
    for (int i = 1; i < 10; i++)
      c[i] += c[i - 1];
    for (int i = a.size() - 1; i >= 0; i--) {
      T x = (a[i] / d) % 10;
      b[c[x] - 1] = a[i];
      c[x]--;
    }
    a = b;
  }
}

