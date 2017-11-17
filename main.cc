#include "binary_search.hh"
#include "utils.hh"

int main() {
  vi a = generate_array_sequence<int>(20);
  print_vector(a);
  bool found = 0;
  int idx = 0;
  binary_search(a, 5, &found, &idx);
  printf("found=%d, idx=%d\n", found, idx);
}

