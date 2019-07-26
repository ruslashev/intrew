#pragma once

#include "util.hh"

template <typename T>
size_t partition_lomuto(std::vector<T> &a, int l, int h) {
  int i = l;
  for (int j = l; j <= h - 1; ++j)
    if (a[j] <= a[h])
      std::swap(a[i++], a[j]);
  std::swap(a[i], a[h]);
  return i;
}

template <typename T>
void quicksort_lomuto(std::vector<T> &a, int l, int h) {
  if (l < h) {
    int m = partition_lomuto(a, l, h);
    quicksort_lomuto(a, l, m - 1);
    quicksort_lomuto(a, m + 1, h);
  }
}

template <typename T>
void quicksort_lomuto(std::vector<T> &a) {
  quicksort_lomuto(a, 0, a.size() - 1);
}

template <typename T>
int partition_hoare(std::vector<T> &a, int l, int h) {
  int i = l - 1, j = h + 1;
  while (1) {
    do {
      --j;
    } while (!(a[j] <= a[l]));
    do {
      i++;
    } while (!(a[i] >= a[l]));
    if (i < j)
      std::swap(a[i], a[j]);
    else
      return j;
  }
}

template <typename T>
void quicksort_hoare(std::vector<T> &a, int l, int h) {
  if (l < h) {
    int m = partition_hoare(a, l, h);
    quicksort_hoare(a, l, m);
    quicksort_hoare(a, m + 1, h);
  }
}

template <typename T>
void quicksort_hoare(std::vector<T> &a) {
  quicksort_hoare(a, 0, a.size() - 1);
}

