#include "2.1_insertion_sort.hh"

int main() {
  v A = generate_vector_random_unique<int>(10);
  print_vector(A);
  insertion_sort(A);
  print_vector(A);
}

