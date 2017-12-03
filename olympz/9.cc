#include "utils.hh"
#include "simple.hh"
#include <map>

int main() {
  int n, numz = 0;
  std::map<int, int> occ;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    ++occ[x];
    if (occ.at(x) > 2)
      ++numz;
  }
  printf("numz=%d\n", numz);
}

