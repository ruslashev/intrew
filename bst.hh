#pragma once

#include <iostream>
#include <vector>
#include <string>

template <typename T>
struct bst_node {
  T key;
  bst_node *left, *right, *parent;

  bst_node(const T &_key, bst_node *_parent = nullptr) : key(_key),
      left(nullptr), right(nullptr), parent(_parent) {}
};

template <typename T>
struct bst {
  bst_node<T> *root;

  bst() : root(nullptr) {}

  void insert(const T &key) {
    bst_node<T> *parent = nullptr, *ins_ptr = root;
    while (ins_ptr != nullptr) {
      parent = ins_ptr;
      ins_ptr = (key < ins_ptr->key) ? ins_ptr->left : ins_ptr->right;
    }
    bst_node<T> *new_node = new bst_node<T>(key, parent);
    if (parent == nullptr)
      root = new_node;
    else {
      if (key < parent->key)
        parent->left = new_node;
      else
        parent->right = new_node;
    }
  }

  void pre_order(bst_node<T> *x) {
    if (!x)
      return;
    pre_order(x->left);
    pre_order(x->right);
    std::cout << x->key << std::endl;
  }

  void print(bst_node<T> *x, int type, const std::string &indent) {
    if (!x)
      return;

    std::string right_indent = indent, left_indent = indent;
    if (type == 1) {
      right_indent += "     ";
      left_indent += " |   ";
    }
    if (type == -1) {
      left_indent += "     ";
      right_indent += " |   ";
    }

    print(x->right, 1, right_indent);

    std::cout << indent;
    if (type == 1)
      std::cout << " /---";
    if (type == -1)
      std::cout << " \\---";
    std::cout << x->key << std::endl;

    print(x->left, -1, left_indent);
  }

  void print() {
    if (root == nullptr)
      std::cout << "<null>" << std::endl;
    else
      print(root, 0, "");
  }
};

