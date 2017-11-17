#include "heapsort.hh"
#include "utils.hh"

int main() {
  vi a = generate_array_random_walk<int>(20, -4, 4);
  print_vector(a);
  heapsort(&a);
  print_vector(a);
}

