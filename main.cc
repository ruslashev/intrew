#include "bst.hh"

int main() {
  bst<int> b;

  b.insert(8);
  b.insert(4);
  b.insert(12);
  b.insert(2);
  b.insert(6);
  b.insert(10);
  b.insert(14);
  b.insert(1);
  b.insert(3);
  b.insert(5);
  b.insert(7);
  b.insert(9);
  b.insert(11);
  b.insert(13);
  b.insert(20);
  b.insert(15);

  b.print();
}

