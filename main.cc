#include "bst.hh"

int main() {
  bst<int> b;
  b.insert(10);
  b.insert(8);
  b.insert(12);
  b.insert(4);
  b.insert(9);
  b.insert(13);
  b.insert(14);
  b.pre_order(b.root);
}

