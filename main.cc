#include "2.3.1_merge_sort.hh"

int main() {
  v A = generate_vector_random_unique<int>(10);
  print_vector(A);
  merge_sort(A);
  print_vector(A);
}

