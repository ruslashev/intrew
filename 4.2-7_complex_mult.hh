#pragma once
#include "util.hh"

void clx_mult(int a, int b, int c, int d, int &x, int &y) {
  int A = a * c, B = b * d;
  x = A - B;
  int C = (a + b) * (c + d);
  y = C - A - B;
}

// alt
void clx_mult2(int a, int b, int c, int d, int &x, int &y) {
  int p1 = c * (a + b), p2 = b * (c + d), p3 = (a - b) * d;
  x = p1 - p2;
  y = p2 + p3;
}

