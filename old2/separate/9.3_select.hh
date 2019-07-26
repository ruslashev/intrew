#pragma once
#include "util.hh"

template <typename T>
T median5(std::vector<T> &a, size_t l, size_t h) {
  for (size_t j = l; j <= h; ++j) {
    T key = a[j - 1];
    size_t i = j - 1;
    while (i >= l && key < a[i - 1]) {
      a[i] = a[i - 1];
      --i;
    }
    a[i] = key;
  }
  size_t n = h - l + 1;
  return n % 2 == 0 ? a[l + n / 2 - 2] : a[l + n / 2 - 1];
}

template <typename T>
T select(std::vector<T> &a, size_t l, size_t h, size_t i) {
  size_t n = h - l + 1, j;
  std::vector<T> medians((n + 4) / 5);
  for (j = 1; j <= n / 5; ++j)
    medians[j - 1] = median5(a, l + (j - 1) * 5, l + (j - 1) * 5 + 4);
  if (n % 5 != 0)
    medians[j - 1] = median5(a, l + (j - 1) * 5, l + (j - 1) * 5 + n % 5 - 1);

  T x = medians.size() == 1 ? medians[0]
    : select(medians, 1, medians.size(), medians.size() / 2);

  size_t k = 0;
  for (size_t j = l, m = l; j <= h; ++j)
    if (a[j - 1] <= x) {
      std::swap(a[m++ - 1], a[j - 1]);
      ++k;
    }

  if (i == k)
    return x;
  else if (i < k)
    return select(a, l, l + k - 1, i);
  else
    return select(a, l + k, h, i - k);
}

template <typename T>
T select(std::vector<T> a, size_t i) {
  return select(a, 1, a.size(), i);
}

