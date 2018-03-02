#include "4.2_matrix_mult.hh"

int main() {
  vector<vector<int>> a = {
    {  6, -4,  4, 2 },
    {  7,  3,  8, 2 },
    {  5,  1,  9, 2 },
    {  2,  1,  9, 2 }
  }, b = {
    {  2,  6,  4, 3 },
    { -2,  7,  3, 3 },
    { -3,  1, -4, 3 },
    {  2,  3,  9, 2 }
  }, c = mat_mult_strassen(a, b);
  for (size_t y = 0; y < c.size(); ++y) {
    for (size_t x = 0; x < c[y].size(); ++x)
      printf("%d ", c[y][x]);
    puts("");
  }
}

