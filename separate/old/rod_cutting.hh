#pragma once

#include "simple.hh"
#include "utils.hh"

int rod_cutting1(v p, int n) {
  if (n == 0)
    return 0;
  int max_cost = p[n - 1];
  for (int i = 1; i < n; ++i)
    max_cost = max(max_cost, rod_cutting1(p, i) + rod_cutting1(p, n - i));
  return max_cost;
}

int rod_cutting2(v p, int n) {
  if (n == 0)
    return 0;
  int max_cost = neginf;
  for (int i = 1; i <= n; ++i)
    max_cost = max(max_cost, p[i - 1] + rod_cutting2(p, n - i));
  return max_cost;
}

static int rod_cutting3_aux(v &memo, v p, int n) {
  if (memo[n] >= 0)
    return memo[n];
  if (n == 0) {
    memo[n] = 0;
    return 0;
  }
  int max_cost = neginf;
  for (int i = 1; i <= n; ++i)
    max_cost = max(max_cost, p[i - 1] + rod_cutting3_aux(memo, p, n - i));
  memo[n] = max_cost;
  return max_cost;
}

int rod_cutting3(v p, int n) {
  v memo(n + 1, neginf);
  return rod_cutting3_aux(memo, p, n);
}

int rod_cutting4(v p, int n) {
  v memo(n + 1);
  memo[0] = 0;
  for (int j = 1; j <= n; ++j) {
    int max_cost = neginf;
    for (int i = 1; i <= j; ++i)
      max_cost = max(max_cost, p[i - 1] + memo[j - i]);
    memo[j] = max_cost;
  }
  return memo[n];
}

