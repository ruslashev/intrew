#include <iostream>

using namespace std;
typedef unsigned long long int ull;

double sat(double n, double s) {
  return n * n * n + 5. * n - 6. * s;
}

double satd(double n) {
  return 3. * n * n + 5.;
}

ull solve(double s) {
  double x = 10e8, h = sat(x, s) / satd(x);
  while (abs(h) >= 0.1) {
    h = sat(x, s) / satd(x);
    x = x - h;
  }
  return x;
}

int main() {
  int t;
  cin >> t;
  ull s;
  for (int i = 0; i < t; ++i) {
    cin >> s;
    cout << solve(s) << endl;
  }
}

