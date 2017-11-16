#include "merge_sort.hh"
#include "utils.hh"

int main() {
  seed();
  vi a = { 5, 2, 4, 6, 1, 3 }; // generate_array_random_unique<int>(20);
  print_vector(a);
  merge_sort(&a);
  print_vector(a);
}

