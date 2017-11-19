#pragma once

#include <chrono>
#include "simple.hh"

typedef std::vector<int> vi;
typedef std::vector<std::vector<int>> vvi;

void seed() {
  srand(time(nullptr));
}

int rand_in_range(int min, int max) {
  return min + rand() % (max - min + 1);
}

template <typename T>
std::vector<T> generate_array_random(int size, int min, int max) {
  std::vector<T> out;
  for (int i = 0; i < size; ++i)
    out.push_back(rand_in_range(min, max));
  return out;
}

template <typename T>
std::vector<T> generate_array_random_walk(int size, int min, int max) {
  T prev = 0;
  std::vector<T> out;
  for (int i = 0; i < size; ++i) {
    out.push_back(prev + rand_in_range(min, max));
    prev = out.back();
  }
  return out;
}

template <typename T>
std::vector<T> generate_array_sequence(int size) {
  std::vector<T> out;
  for (int i = 0; i < size; ++i)
    out.push_back(i + 1);
  return out;
}

template <typename T>
void scramble_array(std::vector<T> *array) {
  for (size_t i = 0; i < array->size(); ++i)
    std::swap((*array)[i], (*array)[rand_in_range(0, array->size() - 1)]);
}

template <typename T>
std::vector<T> generate_array_random_unique(int size) {
  std::vector<T> out = generate_array_sequence<T>(size);
  scramble_array<T>(&out);
  return out;
}

template <typename T>
void print_vector(const std::vector<T> &array) {
  std::cout << "[";
  for (size_t i = 0; i < array.size(); ++i)
    std::cout << array[i] << (i != array.size() - 1 ? " " : "");
  std::cout << "]" << std::endl;
}

template <typename T>
T vector_max(const std::vector<T> &array) {
  T max = array[0];
  for (size_t i = 1; i < array.size(); ++i)
    max = std::max(max, array[i]);
  return max;
}

template <typename T>
T vector_min(const std::vector<T> &array) {
  T min = array[0];
  for (int i = 1; i < (int)array.size(); ++i)
    min = std::min(min, array[i]);
  return min;
}

#define time_execution(X) \
  do { \
    auto begin = std::chrono::high_resolution_clock::now(); \
    X; \
    auto end = std::chrono::high_resolution_clock::now(); \
    std::chrono::duration<double, std::micro> duration = end - begin; \
    printf("%s: %f us\n", #X, duration.count()); \
  } while (0)

