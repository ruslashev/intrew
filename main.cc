#include "6.4_heapsort.hh"

int main() {
  vector<int> a = generate_vector_random<int>(15, 0, 15);
  print_vector(a);
  heapsort(a);
  print_vector(a);
}

