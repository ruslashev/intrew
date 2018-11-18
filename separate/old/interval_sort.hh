#pragma once

#include "simple.hh"

bool int_intersection(interval_t a, interval_t b) {
  return a.left <= b.right && b.left <= a.right;
}

interval_t partition(interval_t A[], int p, int r) {
  interval_t intersection, tmp;

  int pivot = p + rand() % (r - p);
  std::swap(A[pivot], A[r-1]);
  intersection = A[r-1];

  for (int i = p; i < r - 1; i++)
    if (int_intersection(intersection, A[i])) {
      if (A[i].left > intersection.left)
        intersection.left = A[i].left;
      if (A[i].right < intersection.right)
        intersection.right = A[i].right;
    }

  int s;
  for (int i = s = p; i < r - 1; i++)
    if (A[i].right < intersection.left) {
      std::swap(A[i], A[s]);
      s++;
    }
  std::swap(A[r-1], A[s]);

  int t;
  for (int i = r - 1, t = s + 1; t <= i;)
    if (int_intersection(A[i], intersection)) {
      std::swap(A[t], A[i]);
      t++;
    } else
      i--;

  return { s, t };
}

void fuzzy_sort(interval_t array[], int p, int r) {
  if (p < r - 1) {
    interval_t pivot = partition(array, p, r);
    fuzzy_sort(array, p, pivot.left);
    fuzzy_sort(array, pivot.right, r);
  }
}

