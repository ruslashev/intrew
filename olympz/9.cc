#include <map>
#include <iostream>

using namespace std;

int main() {
  int n;
  map<int, int> occ;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    ++occ[x];
  }
  int numz = 0;
  for (auto it = occ.begin(); it != occ.end(); ++it)
    if (it->second > 2)
      ++numz;
  cout << numz << endl;
}

