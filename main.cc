#include "utils.hh"
#include "select.hh"
#include <algorithm>

int main() {
  vi a = generate_array_random_unique<int>(100);
  print_vector(a);
  for (int i = 1; i <= 100; ++i)
    assert(select(a, i) == i);
}

