#pragma once
#include "util.hh"

template <typename T>
struct subarray_t {
  size_t beg, end;
  T sum;
};

template <typename T>
subarray_t<T> find_max_crossing_subarray(const vector<T> &a, size_t beg, size_t mid, size_t end) {
  subarray_t<T> out;
  T sum = 0, left_sum, right_sum;
  bool first_left = true, first_right = true;
  for (int i = mid; i >= (int)beg; --i) {
    sum += a[i];
    if (first_left || sum > left_sum) {
      first_left = false;
      left_sum = sum;
      out.beg = i;
    }
  }
  sum = 0;
  for (size_t j = mid + 1; j <= end; ++j) {
    sum += a[j];
    if (first_right || sum > right_sum) {
      first_right = false;
      right_sum = sum;
      out.end = j;
    }
  }
  out.sum = left_sum + right_sum;
  return out;
}

template <typename T>
subarray_t<T> find_max_subarray(const vector<T> &a, size_t beg, size_t end) {
  if (beg == end)
    return { beg, end, a[beg] };
  size_t mid = (beg + end) / 2;
  subarray_t<T> left = find_max_subarray(a, beg, mid),
    right = find_max_subarray(a, mid + 1, end),
    crossing = find_max_crossing_subarray(a, beg, mid, end);
  if (left.sum >= right.sum && left.sum >= crossing.sum)
    return left;
  if (right.sum >= left.sum && right.sum >= crossing.sum)
    return right;
  return crossing;
}

template <typename T>
subarray_t<T> find_max_subarray(const vector<T> &a) {
  return find_max_subarray(a, 0, a.size() - 1);
}

template <typename T>
subarray_t<T> find_max_subarray_brute(const vector<T> &a, size_t beg, size_t end) {
  subarray_t<T> max = { beg, beg, a[beg] };
  for (size_t i = beg; i <= end; ++i) {
    T sum = 0;
    for (size_t j = i; j <= end; ++j) {
      sum += a[j];
      if (sum > max.sum)
        max = { i, j, sum };
    }
  }
  return max;
}

template <typename T>
subarray_t<T> find_max_subarray_brute(const vector<T> &a) {
  return find_max_subarray_brute(a, 0, a.size() - 1);
}

template <typename T>
subarray_t<T> find_max_subarray_linear(const vector<T> &a) {
  size_t beg = 0, end = 0;
  T w = a[0], max_sum = a[0];
  for (size_t i = 1; i < a.size(); ++i) {
    if (a[i] > w + a[i]) { // can be simplifed to `if (w < 0)' but retains meaning now
      beg = end = i;
      w = a[i];
    } else
      w += a[i];
    if (w > max_sum) {
      max_sum = w;
      end = i;
    }
  }
  return { beg, end, max_sum };
}

