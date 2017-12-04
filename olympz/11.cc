#include "utils.hh"
#include "simple.hh"

int main() {
  string buf, prev = "";
  map<string, map<string, int>> occ;
  while (cin >> buf) {
    if (prev != "")
      ++occ[prev][buf];
    prev = buf;
  }

  ull count = 0;
  for (auto om = occ.begin(); om != occ.end(); ++om) {
    int max_score = om->second.begin()->second;
    for (auto i = om->second.begin(); i != om->second.end(); ++i) {
      if (max_score > 1)
        break;
      max_score = max(max_score, i->second);
    }
    if (max_score > 1)
      ++count;
  }

  cout << count << endl;
  for (auto om = occ.begin(); om != occ.end(); ++om) {
    const auto f = om->second.begin();
    string w = f->first;
    int max_score = f->second;
    for (auto i = om->second.begin(); i != om->second.end(); ++i)
      if (i->second > max_score) {
        max_score = i->second;
        w = i->first;
      }
    if (max_score > 1)
      cout << om->first << " " << w << endl;
  }
}

