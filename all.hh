#pragma once

#include <chrono>
#include <vector>
#include <map>
#include <climits>
#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;
typedef size_t sz;

typedef vector<int> v;
typedef vector<vector<int>> vv;
typedef vector<ull> vu;

const int neginf = INT_MIN, inf = INT_MAX;

struct interval_t {
  int left, right;
};

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

void seed() {
  srand(time(nullptr));
}

int rand_in_range(int min, int max) {
  return min + rand() % (max - min + 1);
}

template <typename T>
std::vector<T> generate_vector_random(int size, int min, int max) {
  std::vector<T> out;
  for (int i = 0; i < size; ++i)
    out.push_back(rand_in_range(min, max));
  return out;
}

template <typename T>
std::vector<T> generate_vector_random_walk(int size, int min, int max) {
  T prev = 0;
  std::vector<T> out;
  for (int i = 0; i < size; ++i) {
    out.push_back(prev + rand_in_range(min, max));
    prev = out.back();
  }
  return out;
}

template <typename T>
std::vector<T> generate_vector_sequence(int size) {
  std::vector<T> out;
  for (int i = 0; i < size; ++i)
    out.push_back(i + 1);
  return out;
}

template <typename T>
void scramble_vector(std::vector<T> &vector) {
  for (size_t i = 0; i < vector.size(); ++i)
    std::swap(vector[i], vector[rand_in_range(0, vector.size() - 1)]);
}

template <typename T>
std::vector<T> generate_vector_random_unique(int size) {
  std::vector<T> out = generate_vector_sequence<T>(size);
  scramble_vector<T>(out);
  return out;
}

template <typename T>
void print_vector(const std::vector<T> &vector, bool newline = true) {
  std::cout << "[";
  for (size_t i = 0; i < vector.size(); ++i)
    std::cout << vector[i] << (i != vector.size() - 1 ? " " : "");
  std::cout << "]";
  if (newline)
    std::cout << std::endl;
}

template <typename T>
T vector_max(const std::vector<T> &vector) {
  T max = vector[0];
  for (size_t i = 1; i < vector.size(); ++i)
    max = std::max(max, vector[i]);
  return max;
}

template <typename T>
T vector_min(const std::vector<T> &vector) {
  T min = vector[0];
  for (int i = 1; i < (int)vector.size(); ++i)
    min = std::min(min, vector[i]);
  return min;
}

#define time_execution(X) \
  do { \
    auto begin = std::chrono::high_resolution_clock::now(); \
    X; \
    auto end = std::chrono::high_resolution_clock::now(); \
    std::chrono::duration<double, std::micro> duration = end - begin; \
    printf("%s: %fus (%fms)\n", #X, duration.count(), duration.count() / 1000.); \
  } while (0)

// 2.1 insertion sort
template <typename T>
void insertion_sort(vector<T> &A) {
  for (size_t i = 1; i < A.size(); ++i) {
    const T key = A[i];
    size_t j = i - 1;
    for (; j >= 0 && A[j] > key; --j)
      A[j + 1] = A[j];
    A[j + 1] = key;
  }
}

// 2.3.1 merge sort
// warning: uses 'inf' even though vector elements are templated
template <typename T>
static void _merge_unused(vector<T> &a, int beg, int mid, int end) {
  vector<T> left(mid - beg + 1), right(end - mid);
  for (size_t i = 0; i < left.size(); ++i)
    left[i] = a[beg + i];
  for (size_t j = 0; j < right.size(); ++j)
    right[j] = a[mid + j + 1];
  left.push_back(inf);
  right.push_back(inf);
  for (int i = 0, j = 0, k = beg; k <= end; ++k)
    if (left[i] <= right[j])
      a[k] = left[i++];
    else
      a[k] = right[j++];
}

template <typename T>
static void merge(vector<T> &a, int beg, int mid, int end) {
  vector<T> left(mid - beg + 1), right(end - mid);
  for (size_t i = 0; i < left.size(); ++i)
    left[i] = a[beg + i];
  for (size_t j = 0; j < right.size(); ++j)
    right[j] = a[mid + j + 1];
  size_t i = 0, j = 0, k = beg;
  for (; i < left.size() && j < right.size(); ++k)
    if (left[i] <= right[j])
      a[k] = left[i++];
    else
      a[k] = right[j++];
  for (; i != left.size(); ++k, ++i)
    a[k] = left[i];
  for (; j != right.size(); ++k, ++j)
    a[k] = right[j];
}

template <typename T>
static void merge_sort(vector<T> &a, int beg, int end) {
  if (end - beg >= 1) {
    sz mid = (beg + end) / 2;
    merge_sort(a, beg, mid);
    merge_sort(a, mid + 1, end);
    merge(a, beg, mid, end);
  }
}

template <typename T>
void merge_sort(vector<T> &a) {
  merge_sort(a, 0, a.size() - 1);
}

// 2.3-5 binary search
template <typename T>
bool binary_search(const vector<T> &a, T needle) {
  int beg = 0, end = a.size() - 1;
  while (beg <= end) {
    sz mid = (beg + end) / 2;
    if (needle < a[mid])
      end = mid - 1;
    else if (needle > a[mid])
      beg = mid + 1;
    else
      return true;
  }
  return false;
}

// 2.3-7 two integer sum
// O(n lb n)
template <typename T>
bool sum_exists(vector<T> a, int x) {
  // `a` is supposed to be a set
  merge_sort(a);
  for (size_t i = 0; i < a.size(); ++i) {
    if (x - a[i] != a[i] && binary_search(a, x - a[i])) {
      return true;
    }
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

