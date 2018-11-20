#include "all.hh"

int main() {
  int n = 18;
  v p = generate_vector_random_walk<int>(n, 1, 10);
  print_vector(p);
  time_execution(rod_cutting1(p, n));
  time_execution(rod_cutting2(p, n));
  time_execution(rod_cutting3(p, n));
  time_execution(rod_cutting4(p, n));
}

