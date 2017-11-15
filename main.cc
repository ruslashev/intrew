#include "utils.hh"

int main() {
  seed();
  vi a = generate_array_sequence<int>(20);
  scramble_array(&a);
  print_vector(a);
}

