#pragma once

#include <vector>
#include <string>
using std::vector;
using std::string;

template <typename T>
struct rb_node {
  T key;
  bool black;
  rb_node *left, *right, *parent;

  rb_node() : black(true), left(nullptr), right(nullptr), parent(nullptr) {}
  rb_node(T _key, rb_node *_parent = nullptr, bool _black = true
      , rb_node *_left = nullptr, rb_node *_right = nullptr)
    : black(_black), left(_left), right(_right), parent(_parent), key(_key) {}
};

template <typename T>
struct rb_tree {
  rb_node<T> *root;
  rb_tree() : root(nullptr) {}

  rb_node<T>* minimum() {
    rb_node<T> *x = root;
    if (root == nullptr)
      return nullptr;
    while (x->left != nullptr)
      x = x->left;
    return x;
  }

  rb_node<T>* maximum() {
    rb_node<T> *x = root;
    if (root == nullptr)
      return nullptr;
    while (x->right != nullptr)
      x = x->right;
    return x;
  }

  rb_node<T>* minimum(rb_node<T> *x) {
    while (x->left != nullptr)
      x = x->left;
    return x;
  }

  rb_node<T>* maximum(rb_node<T> *x) {
    while (x->right != nullptr)
      x = x->right;
    return x;
  }

  rb_node<T>* succ(rb_node<T> *x) {
    if (x->right != nullptr)
      return minimum(x->right);
    rb_node<T> *y = x->parent;
    while (y != nullptr && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  rb_node<T>* pred(rb_node<T> *x) {
    if (x->left != nullptr)
      return tree_maximum(x->left);
    rb_node<T> *y = x->parent;
    while (y != nullptr && x == y->left) {
      x = y;
      y = y->parent;
    }
    return y;
  }

};

template <typename T>
void left_rotate(rb_tree<T> &t, rb_node<T> *x) {
  rb_node<T> *y = x->right;
  x->right = y->left;
  if (y->left != nullptr)
    y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == nullptr)
    t.root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

template <typename T>
void right_rotate(rb_tree<T> &t, rb_node<T> *x) {
  rb_node<T> *y = x->left;
  x->left = y->right;
  if (y->right != nullptr)
    y->right->parent = x;
  y->parent = x->parent;
  if (x->parent == nullptr)
    t.root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->right = x;
  x->parent = y;
}

template <typename T>
void rb_insert(rb_tree<T> &t, rb_node<T> *z) {
  rb_node<T> *y = nullptr, *x = t.root;
  while (x != nullptr) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y;
  if (y == nullptr)
    t.root = z;
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
  z->left = nullptr;
  z->right = nullptr;
  z->black = false;
  rb_insert_fixup(t, z);
}

template <typename T>
void rb_insert_fixup(rb_tree<T> &t, rb_node<T> *z) {
  while (z->parent != nullptr && z->parent->black == false)
    if (z->parent == z->parent->parent->left) {
      rb_node<T> *y = z->parent->parent->right;
      if (y != nullptr && y->black == false) {
        z->parent->black = true;
        y->black = true;
        z->parent->parent->black = false;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->black = true;
        z->parent->parent->black = false;
        right_rotate(t, z->parent->parent);
      }
    } else {
      rb_node<T> *y = z->parent->parent->left;
      if (y != nullptr && y->black == false) {
        z->parent->black = true;
        y->black = true;
        z->parent->parent->black = false;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          right_rotate(t, z);
        }
        z->parent->black = true;
        z->parent->parent->black = false;
        left_rotate(t, z->parent->parent);
      }
    }
  t.root->black = true;
}

template <typename T>
void rb_transplant(rb_tree<T> &t, rb_node<T> *u, rb_node<T> *v) {
  if (u->parent == nullptr)
    t.root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v != nullptr)
    v->parent = u->parent;
}

template <typename T>
void rb_delete(rb_tree<T> &t, rb_node<T> *z) {
  rb_node<T> *y = z, *x;
  bool y_orig_color = y->black;
  if (z->left == nullptr) {
    x = z->right;
    rb_transplant(t, z, z->right);
  } else if (z->right == nullptr) {
    x = z->left;
    rb_transplant(t, z, z->left);
  } else {
    y = tree_minimum(z->right);
    y_orig_color = y->black;
    x = y->right;
    if (y->parent == z) {
      if (x != nullptr)
        x->parent = y;
    } else {
      rb_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rb_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->black = z->black;
  }
  if (y_orig_color == true)
    rb_delete_fixup(t, x);
}

// does not work correctly: uses nullptrs and so is prone to segfaults
template <typename T>
void rb_delete_fixup(rb_tree<T> &t, rb_node<T> *x) {
  while (x != t.root && x->black == true) {
    if (x == x->parent->left) {
      rb_node<T> *w = x->parent->right;
      if (w->black == false) {
        w->black = true;
        x->parent->black = false;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }
      if (w->left->black == true && w->right->black == true) {
        w->black = false;
        x = x->parent;
      } else {
        if (w->right->black == true) {
          w->left->black = true;
          w->black = false;
          right_rotate(t, w);
          w = x->parent->right;
        }
        w->black = x->parent->black;
        x->parent->black = true;
        w->right->black = true;
        left_rotate(t, x->parent);
        x = t.root;
      }
    } else {
      rb_node<T> *w = x->parent->left;
      if (w->black == false) {
        w->black = true;
        x->parent->black = false;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      if (w->right->black == true && w->left->black == true) {
        w->black = false;
        x = x->parent;
      } else {
        if (w->left->black == true) {
          w->right->black = true;
          w->black = false;
          left_rotate(t, w);
          w = x->parent->left;
        }
        w->black = x->parent->black;
        x->parent->black = true;
        w->right->black = true;
        right_rotate(t, x->parent);
        x = t.root;
      }
    }
  }
  x->black = true;
}

