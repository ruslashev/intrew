#pragma once

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
#define repi(i,a,b) for (int i = a; i <= b; ++i)
#define repx(i,a,b) for (int i = a; i < b; ++i)

const int neginf = INT_MIN, inf = INT_MAX;

struct subarray_t {
  int start, end, sum;
};

struct interval_t {
  int left, right;
};

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

