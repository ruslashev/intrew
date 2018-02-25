#include "2.3-7_two_integer_sum.hh"

int main() {
  v a = generate_vector_random_unique<int>(10);
  print_vector(a);
  for (int i = -5; i <= 20; ++i)
    printf("sum_exists_better(a, %d)=%d\n", i, sum_exists_better(a, i));
}

