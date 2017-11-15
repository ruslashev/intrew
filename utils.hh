#pragma once

#include <vector>
#include <climits>
#include <cassert>
#include <cmath>
#include <iostream>

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

typedef long long int ll;
typedef unsigned long long int ull;

const int neginf = INT_MIN, inf = INT_MAX;

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

template <typename T> void scramble_array(std::vector<T> *array) {
  for (size_t i = 0; i < array->size(); ++i)
    std::swap((*array)[i], (*array)[rand_in_range(0, array->size() - 1)]);
}

template <typename T>
void print_vector(const std::vector<T> &array) {
  std::cout << "[";
  for (size_t i = 0; i < array.size(); ++i)
    std::cout << array[i] << (i != array.size() - 1 ? " " : "");
  std::cout << "]" << std::endl;
}

