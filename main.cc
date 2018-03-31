#include "7.1_quicksort.hh"

int main() {
  vector<int> a = generate_vector_random_unique<int>(9);
  print_vector(a);
  quicksort_hoare(a);
  print_vector(a);
}

