#include "utils.hh"
#include "simple.hh"
#include <map>

static std::map<int, bool> memo; // absolutamente asqueroso

bool is_prime(int n) {
  if (n == 2 || n == 3)
    return true;
  if ((n % 2 == 0) || (n % 3 == 0))
    return false;

  int i = 5, w = 2;
  while (i * i <= n) {
    if (n % i == 0)
      return false;
    i += w;
    w = 6 - w;
  }

  return true;
}

bool is_semiprime(int n) {
  if (memo.count(n)) {
    printf("is_semiprime(%d) = %d\n", n, memo.at(n));
    return memo.at(n);
  }
  int x = n, p, f = 0;
  for (p = 2; f < 2 && p * p <= n; p++)
    while (n % p == 0) {
      n /= p;
      f++;
    }
  bool r = (n > 1) ? f == 1 : 0;
  memo[x] = r;
  printf("is_semiprime(%d) = %d\n", x, r);
  return r;
}

int main() {
  vi as;

  int n;
  cin >> n;
  as.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> as[i];

  for (int i = 0; i < n; ++i) {
    int x = as[i], semiprimes = 0;
    printf("x=%d\n", x);
    for (int j = 2; j * j <= x; ++j)
      if (x % j == 0) {
        semiprimes += is_semiprime(j);
        if (j != x / j)
          semiprimes += is_semiprime(x / j);
      }
    cout << semiprimes << endl;
  }
}

