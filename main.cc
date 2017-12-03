#include "rod_cutting.hh"
#include "utils.hh"
#include "simple.hh"

int main() {
  v p = {1,5,8,9,10,17,17,20,24,30,31,35,39,41,50,51};
  for (int i = 0; i < p.size(); ++i) {
    printf("i=%d\n", i);
    int b, c, d;
    time_execution(b = rod_cutting2(p, i));
    time_execution(c = rod_cutting3(p, i));
    time_execution(d = rod_cutting4(p, i));
    printf("b=%d, c=%d, d=%d\n", b, c, d);
    assert(b == c);
    assert(c == d);
  }
}

