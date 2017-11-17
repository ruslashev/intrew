#include "maximum_subarray.hh"
#include "utils.hh"

int main() {
  for (int i = 0; i < 2e2; ++i) {
    vi a = generate_array_random<int>(1e5, -1e3, 1e3);
    subarray_t x = find_maximum_subarray_dc(a)
      , y = find_maximum_subarray(a);
    assert(x.sum == y.sum);
  }
}

