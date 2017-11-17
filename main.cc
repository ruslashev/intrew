#include "merge_sort.hh"
#include "utils.hh"

int main() {
  vi a = generate_array_random_unique<int>(1e6);
  time_execution(merge_sort(&a));
}

