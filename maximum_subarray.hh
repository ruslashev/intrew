#pragma once

#include "simple.hh"

template <typename T>
static subarray_t _find_max_crossing_subarray(std::vector<T> &A, size_t low
    , size_t mid, size_t high) {
  int left_sum = neginf, max_left = 0, sum = 0;
  for (size_t i = mid; i >= low; --i) {
    sum += A[i - 1];
    if (sum > left_sum) {
      left_sum = sum;
      max_left = i;
    }
  }
  int right_sum = neginf, max_right = 0;
  sum = 0;
  for (size_t i = mid + 1; i <= high; ++i) {
    sum += A[i - 1];
    if (sum > right_sum) {
      right_sum = sum;
      max_right = i;
    }
  }
  return { max_left, max_right, left_sum + right_sum };
}

template <typename T>
static subarray_t _find_maximum_subarray_dc(std::vector<T> &A, int low, int high) {
  if (high == low)
    return { low, high, A[low - 1] };
  else {
    int mid = (low + high) / 2;
    subarray_t left = _find_maximum_subarray_dc(A, low, mid)
      , right = _find_maximum_subarray_dc(A, mid + 1, high)
      , crossing = _find_max_crossing_subarray(A, low, mid, high);
    if (left.sum >= right.sum && left.sum >= crossing.sum)
      return { left.start, left.end, left.sum };
    else if (right.sum >= left.sum && right.sum >= crossing.sum)
      return { right.start, right.end, right.sum };
    else
      return { crossing.start, crossing.end, crossing.sum };
  }
}

template <typename T>
subarray_t find_maximum_subarray_dc(std::vector<T> &A) {
  return _find_maximum_subarray_dc(A, 1, A.size());
}

template <typename T>
subarray_t find_maximum_subarray(std::vector<T> &A) {
  int max_sum_ending_here = A[0], max_sum_so_far = A[0];
  int max_start_here = 1, max_end_here = 1,
      max_start_so_far = 1, max_end_so_far = 1;
  for (size_t i = 2; i <= A.size(); ++i) {
    int v = A[i - 1];
    if (v > max_sum_ending_here + v) {
      max_sum_ending_here = v;
      max_start_here = i;
      max_end_here = i;
    } else {
      max_sum_ending_here = max_sum_ending_here + v;
      max_end_here = i;
    }
    if (max_sum_ending_here > max_sum_so_far) {
      max_sum_so_far = max_sum_ending_here;
      max_start_so_far = max_start_here;
      max_end_so_far = max_end_here;
    }
  }
  return { max_start_so_far, max_end_so_far, max_sum_so_far };
}

