#include <iostream>
#include <map>
#include <set>
using namespace std;

typedef unsigned long long ull;
typedef unsigned long ul;
typedef pair<ul,ul> pair_t;

bool doesnt_include(const set<ul> &s, ul v) {
  return s.count(v) == 0;
}

set<ul> merge(const set<ul> &_cont1, const set<ul> &_cont2) {
  set<ul> cont = _cont1;
  cont.insert(_cont2.begin(), _cont2.end());
  return cont;
}

set<ul> cons(ul _first, ul _second) {
  set<ul> cont;
  cont.insert(_first);
  cont.insert(_second);
  return cont;
}

int main() {
  int high = 1;
  ul v, e;
  cin >> v >> e;
  map<pair<ul,ul>, pair<set<ul>,int>> lengths;
  for (ul i = 1; i <= e; ++i) {
    ul v1, v2;
    cin >> v1 >> v2;

    const pair_t pf(v1, v2), pr(v2, v1);
    const set<ul> pc = cons(v1, v2);
    if (!lengths.count(pf) && !lengths.count(pr))
      lengths[pf] = { pc, 1 };

    for (auto it = lengths.begin(); it != lengths.end(); ++it) {
      const pair_t p = it->first;
      if (p == pf)
        continue;
      const set<ul> c = it->second.first;
      int s = it->second.second;
      bool di2 = doesnt_include(c, v2), di1 = doesnt_include(c, v1);
      const set<ul> pUpf = merge(c, pc);
      if (p.second == v1 && p.first != v2 && di2) {
        const pair_t n(p.first, v2);
        if (s + 1 > lengths[n].second) {
          lengths[n] = { pUpf, s + 1 };
          high = max(high, s + 1);
        }
      }
      if (v2 == p.first && v1 != p.second && di1) {
        const pair_t n(v1, p.second);
        if (s + 1 > lengths[n].second) {
          lengths[n] = { pUpf, s + 1 };
          high = max(high, s + 1);
        }
      }
      if (p.first == v1 && p.second != v2 && di2) {
        const pair_t n(p.second, v2);
        if (s + 1 > lengths[n].second) {
          lengths[n] = { pUpf, s + 1 };
          high = max(high, s + 1);
        }
      }
      if (v2 == p.second && v1 != p.first && di1) {
        const pair_t n(v1, p.first);
        if (s + 1 > lengths[n].second) {
          lengths[n] = { pUpf, s + 1 };
          high = max(high, s + 1);
        }
      }
    }
  }

  cout << high << endl;
}

