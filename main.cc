#include "maximum_subarray.hh"
#include "utils.hh"

int main() {
  vi a = generate_array_random_walk<int>(20, -4, 4);
  print_vector(a);
  subarray_t x = find_maximum_subarray(a);
  printf("x.start=%d, x.end=%d, x.sum=%d\n", x.start, x.end, x.sum);
  for (int i = x.start; i < x.end; ++i)
    printf("%d%s", a[i], (i == x.end - 1) ? "\n" : " ");
}

