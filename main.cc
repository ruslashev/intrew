#include "4.1_maximum_subarray.hh"

int main() {
  vector<int> a = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
  subarray_t<int> s = find_max_subarray_linear(a);
  printf("s.beg=%d, s.end=%d, s.sum=%d\n", s.beg, s.end, s.sum);
}

