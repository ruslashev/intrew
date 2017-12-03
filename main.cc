#include "matrix_mult.hh"
#include "utils.hh"
#include "simple.hh"

int main() {
  v p = {5,10,3,12,5,50,6};
  mult_result_t r = matrix_chain_order(p);
  print_optimal_parens(r.s, 1, 6);
  puts("");
  repx(y, 0, 6) {
    repx(x, 0, 6)
      printf("%d\t", r.m[y][x]);
    puts("");
  }
  printf("r.m[0][5]=%d\n", r.m[0][5]);
}

