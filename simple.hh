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

struct subarray_t {
  int start, end, sum;
};

struct interval_t {
  int left, right;
};

