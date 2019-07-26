#pragma once

#include "simple.hh"

struct mult_result_t {
  vv m, s;
};

mult_result_t matrix_chain_order(v p) {
  int n = p.size() - 1;
  vv m(n + 1, v(n + 1)), s(n, v(n + 1));
  repi(i, 1, n)
    m[i - 1][i - 1] = 0;
  repi(l, 2, n)
    repi(i, 1, n - l + 1) {
      int j = i + l - 1;
      m[i - 1][j - 1] = inf;
      repi(k, i, j - 1) {
        int q = m[i - 1][k - 1] + m[k + 1 - 1][j - 1] + p[i - 1] * p[k] * p[j];
        if (q < m[i - 1][j - 1]) {
          m[i - 1][j - 1] = q;
          s[i - 1][j - 1] = k;
        }
      }
    }
  return { m, s };
}

void print_optimal_parens(const vv &s, int i, int j) {
  if (i == j)
    printf("A%d", i);
  else {
    printf("(");
    print_optimal_parens(s, i, s[i - 1][j - 1]);
    print_optimal_parens(s, s[i - 1][j - 1] + 1, j);
    printf(")");
  }
}

