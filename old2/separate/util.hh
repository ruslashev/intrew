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

