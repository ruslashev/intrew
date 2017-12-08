#include <map>
#include <iostream>

using namespace std;
typedef unsigned long long int ull;

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
    bool start = true, equal_to_this = false;
    for (auto i = om->second.begin(); i != om->second.end(); ++i) {
      if (start) {
        start = 0;
        continue;
      }
      if (i->second > max_score) {
        max_score = i->second;
        equal_to_this = false;
      } else if (i->second == max_score)
        equal_to_this = true;
    }
    if (max_score > 1 && !equal_to_this)
      ++count;
  }

  cout << count << endl;
  for (auto om = occ.begin(); om != occ.end(); ++om) {
    const auto f = om->second.begin();
    string w = f->first;
    int max_score = f->second;
    bool start = true, equal_to_this = false;
    for (auto i = om->second.begin(); i != om->second.end(); ++i) {
      if (start) {
        start = 0;
        continue;
      }
      if (i->second > max_score) {
        max_score = i->second;
        w = i->first;
        equal_to_this = false;
      } else if (i->second == max_score)
        equal_to_this = true;
    }
    if (max_score > 1 && !equal_to_this)
      cout << om->first << " " << w << endl;
  }
}

