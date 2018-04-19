#pragma once

#include <iostream>

template <typename T>
struct bst_node {
  T data;
  bst_node *left, *right, *parent;

  bst_node(const T &_data, bst_node *_parent = nullptr) : data(_data),
      left(nullptr), right(nullptr), parent(_parent) {}
};

template <typename T>
struct bst {
  bst_node<T> *root;

  bst() : root(nullptr) {}
  void insert(const T &data) {
    bst_node<T> *parent, *ins_ptr = root;
    while (ins_ptr != nullptr) {
      parent = ins_ptr;
      ins_ptr = (data < ins_ptr->data) ? ins_ptr->left : ins_ptr->right;
    }
    bst_node<T> *new_node = new bst_node<T>(data, parent);
    if (parent == nullptr)
      root = new_node;
    else {
      if (data < parent->data)
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
    std::cout << x->data << std::endl;
  }
};

