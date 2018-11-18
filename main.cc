#include "all.hh"

int main() {
  v a = generate_vector_random_walk<int>(10, 5, 10);
  print_vector(a);
}

