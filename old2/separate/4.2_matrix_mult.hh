#pragma once
#include "util.hh"

template <typename T>
vector<vector<T>> mat_mult_naive(const vector<vector<T>> &a, const vector<vector<T>> &b) {
  size_t n = a.size();
  vector<vector<T>> c(n, vector<T>(n, 0));
  for (size_t y = 0; y < n; ++y)
    for (size_t x = 0; x < n; ++x)
      for (size_t k = 0; k < n; ++k)
        c[y][x] += a[y][k] * b[k][x];
  return c;
}

template <typename T>
vector<vector<T>> mat_add(const vector<vector<T>> &a, const vector<vector<T>> &b) {
  size_t n = a.size();
  vector<vector<T>> c(n, vector<T>(n, 0));
  for (size_t y = 0; y < n; ++y)
    for (size_t x = 0; x < n; ++x)
        c[y][x] = a[y][x] + b[y][x];
  return c;
}

template <typename T>
vector<vector<T>> mat_sub(const vector<vector<T>> &a, const vector<vector<T>> &b) {
  size_t n = a.size();
  vector<vector<T>> c(n, vector<T>(n, 0));
  for (size_t y = 0; y < n; ++y)
    for (size_t x = 0; x < n; ++x)
        c[y][x] = a[y][x] - b[y][x];
  return c;
}

// only works for square matrices with power of 2 dimensions
template <typename T>
vector<vector<T>> mat_mult_strassen(const vector<vector<T>> &a, const vector<vector<T>> &b) {
  size_t n = a.size();
  vector<vector<T>> zero(n, vector<T>(n, 0)), zerohalf(n / 2, vector<T>(n / 2, 0)),
    c, a11, a12, a21, a22, b11, b12, b21, b22, c11, c12, c21, c22, s1, s2, s3,
    s4, s5, s6, s7, s8, s9, s10, p1, p2, p3, p4, p5, p6, p7;

  c = zero;
  a11 = a12 = a21 = a22 = b11 = b12 = b21 = b22 = zerohalf;

  if (n == 2)
    return mat_mult_naive(a, b);
  for (size_t i = 0; i < n / 2; ++i)
    for (size_t j = 0; j < n / 2; ++j) {
      a11[i][j] = a[i][j];
      a12[i][j] = a[i][j + n / 2];
      a21[i][j] = a[i + n / 2][j];
      a22[i][j] = a[i + n / 2][j + n / 2];
      b11[i][j] = b[i][j];
      b12[i][j] = b[i][j + n / 2];
      b21[i][j] = b[i + n / 2][j];
      b22[i][j] = b[i + n / 2][j + n / 2];
    }

  s1 =  mat_sub(b12, b22);
  s2 =  mat_add(a11, a12);
  s3 =  mat_add(a21, a22);
  s4 =  mat_sub(b21, b11);
  s5 =  mat_add(a11, a22);
  s6 =  mat_add(b11, b22);
  s7 =  mat_sub(a12, a22);
  s8 =  mat_add(b21, b22);
  s9 =  mat_sub(a11, a21);
  s10 = mat_add(b11, b12);

  p1 = mat_mult_strassen(a11, s1);
  p2 = mat_mult_strassen(s2, b22);
  p3 = mat_mult_strassen(s3, b11);
  p4 = mat_mult_strassen(a22, s4);
  p5 = mat_mult_strassen(s5, s6);
  p6 = mat_mult_strassen(s7, s8);
  p7 = mat_mult_strassen(s9, s10);

  c11 = mat_add(p5, p4);
  c11 = mat_sub(c11, p2);
  c11 = mat_add(c11, p6);

  c12 = mat_add(p1, p2);

  c21 = mat_add(p3, p4);

  c22 = mat_add(p5, p1);
  c22 = mat_sub(c22, p3);
  c22 = mat_sub(c22, p7);

  for (size_t i = 0; i < n / 2; ++i)
    for (size_t j = 0; j < n / 2; ++j) {
      c[i][j] = c11[i][j];
      c[i][j + n / 2] = c12[i][j];
      c[i + n / 2][j] = c21[i][j];
      c[i + n / 2][j + n / 2] = c22[i][j];
    }

  return c;
}

