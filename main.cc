#include "9.3_select.hh"

int main() {
  vector<int> a = generate_vector_random_unique<int>(130);
  printf("select(a, 99)=%d\n", select(a, 99));
}

