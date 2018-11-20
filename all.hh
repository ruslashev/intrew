#pragma once

#include <chrono>
#include <vector>
#include <map>
#include <climits>
#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;
typedef size_t sz;

typedef vector<int> v;
typedef vector<vector<int>> vv;
typedef vector<ull> vu;

const int neginf = INT_MIN, inf = INT_MAX;

struct interval_t {
  int left, right;
};

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

void seed() {
  srand(time(nullptr));
}

int rand_in_range(int min, int max) {
  return min + rand() % (max - min + 1);
}

template <typename T>
std::vector<T> generate_vector_random(int size, int min, int max) {
  std::vector<T> out;
  for (int i = 0; i < size; ++i)
    out.push_back(rand_in_range(min, max));
  return out;
}

template <typename T>
std::vector<T> generate_vector_random_walk(int size, int min, int max) {
  T prev = 0;
  std::vector<T> out;
  for (int i = 0; i < size; ++i) {
    out.push_back(prev + rand_in_range(min, max));
    prev = out.back();
  }
  return out;
}

template <typename T>
std::vector<T> generate_vector_sequence(int size) {
  std::vector<T> out;
  for (int i = 0; i < size; ++i)
    out.push_back(i + 1);
  return out;
}

template <typename T>
void scramble_vector(std::vector<T> &vector) {
  for (size_t i = 0; i < vector.size(); ++i)
    std::swap(vector[i], vector[rand_in_range(0, vector.size() - 1)]);
}

template <typename T>
std::vector<T> generate_vector_random_unique(int size) {
  std::vector<T> out = generate_vector_sequence<T>(size);
  scramble_vector<T>(out);
  return out;
}

template <typename T>
void print_vector(const std::vector<T> &vector, bool newline = true) {
  std::cout << "[";
  for (size_t i = 0; i < vector.size(); ++i)
    std::cout << vector[i] << (i != vector.size() - 1 ? " " : "");
  std::cout << "]";
  if (newline)
    std::cout << std::endl;
}

template <typename T>
T vector_max(const std::vector<T> &vector) {
  T max = vector[0];
  for (size_t i = 1; i < vector.size(); ++i)
    max = std::max(max, vector[i]);
  return max;
}

template <typename T>
T vector_min(const std::vector<T> &vector) {
  T min = vector[0];
  for (int i = 1; i < (int)vector.size(); ++i)
    min = std::min(min, vector[i]);
  return min;
}

#define time_execution(X) \
  do { \
    auto begin = std::chrono::high_resolution_clock::now(); \
    X; \
    auto end = std::chrono::high_resolution_clock::now(); \
    std::chrono::duration<double, std::micro> duration = end - begin; \
    printf("%s: %fus (%fms)\n", #X, duration.count(), duration.count() / 1000.); \
  } while (0)

// 2.1 insertion sort
template <typename T>
void insertion_sort(vector<T> &A) {
  for (size_t i = 1; i < A.size(); ++i) {
    const T key = A[i];
    size_t j = i - 1;
    for (; j >= 0 && A[j] > key; --j)
      A[j + 1] = A[j];
    A[j + 1] = key;
  }
}

// 2.3.1 merge sort
// warning: uses 'inf' even though vector elements are templated
template <typename T>
static void _merge_unused(vector<T> &a, int beg, int mid, int end) {
  vector<T> left(mid - beg + 1), right(end - mid);
  for (size_t i = 0; i < left.size(); ++i)
    left[i] = a[beg + i];
  for (size_t j = 0; j < right.size(); ++j)
    right[j] = a[mid + j + 1];
  left.push_back(inf);
  right.push_back(inf);
  for (int i = 0, j = 0, k = beg; k <= end; ++k)
    if (left[i] <= right[j])
      a[k] = left[i++];
    else
      a[k] = right[j++];
}

template <typename T>
static void merge(vector<T> &a, int beg, int mid, int end) {
  vector<T> left(mid - beg + 1), right(end - mid);
  for (size_t i = 0; i < left.size(); ++i)
    left[i] = a[beg + i];
  for (size_t j = 0; j < right.size(); ++j)
    right[j] = a[mid + j + 1];
  size_t i = 0, j = 0, k = beg;
  for (; i < left.size() && j < right.size(); ++k)
    if (left[i] <= right[j])
      a[k] = left[i++];
    else
      a[k] = right[j++];
  for (; i != left.size(); ++k, ++i)
    a[k] = left[i];
  for (; j != right.size(); ++k, ++j)
    a[k] = right[j];
}

template <typename T>
static void merge_sort(vector<T> &a, int beg, int end) {
  if (end - beg >= 1) {
    sz mid = (beg + end) / 2;
    merge_sort(a, beg, mid);
    merge_sort(a, mid + 1, end);
    merge(a, beg, mid, end);
  }
}

template <typename T>
void merge_sort(vector<T> &a) {
  merge_sort(a, 0, a.size() - 1);
}

// 2.3-5 binary search
template <typename T>
bool binary_search(const vector<T> &a, T needle) {
  int beg = 0, end = a.size() - 1;
  while (beg <= end) {
    sz mid = (beg + end) / 2;
    if (needle < a[mid])
      end = mid - 1;
    else if (needle > a[mid])
      beg = mid + 1;
    else
      return true;
  }
  return false;
}

// 2.3-7 two integer sum
// O(n lb n)
template <typename T>
bool sum_exists(vector<T> a, int x) {
  // `a` is supposed to be a set
  merge_sort(a);
  for (size_t i = 0; i < a.size(); ++i) {
    if (x - a[i] != a[i] && binary_search(a, x - a[i])) {
      return true;
    }
  }
  return false;
}

template <typename T>
bool sum_exists_better(vector<T> a, int x) {
  map<int, int> seen;
  for (size_t i = 0; i < a.size(); ++i) {
    if (seen.count(x - a[i]) > 0)
      return true;
    seen[a[i]] = 1337;
  }
  return false;
}

// 4.1 maximum subarray
template <typename T>
struct subarray_t {
  size_t beg, end;
  T sum;
};

template <typename T>
static subarray_t<T> find_max_crossing_subarray(const vector<T> &a, size_t beg, size_t mid, size_t end) {
  subarray_t<T> out;
  T sum = 0, left_sum, right_sum;
  bool first_left = true, first_right = true;
  for (int i = mid; i >= (int)beg; --i) {
    sum += a[i];
    if (first_left || sum > left_sum) {
      first_left = false;
      left_sum = sum;
      out.beg = i;
    }
  }
  sum = 0;
  for (size_t j = mid + 1; j <= end; ++j) {
    sum += a[j];
    if (first_right || sum > right_sum) {
      first_right = false;
      right_sum = sum;
      out.end = j;
    }
  }
  out.sum = left_sum + right_sum;
  return out;
}

template <typename T>
subarray_t<T> find_max_subarray(const vector<T> &a, size_t beg, size_t end) {
  if (beg == end)
    return { beg, end, a[beg] };
  size_t mid = (beg + end) / 2;
  subarray_t<T> left = find_max_subarray(a, beg, mid),
    right = find_max_subarray(a, mid + 1, end),
    crossing = find_max_crossing_subarray(a, beg, mid, end);
  if (left.sum >= right.sum && left.sum >= crossing.sum)
    return left;
  if (right.sum >= left.sum && right.sum >= crossing.sum)
    return right;
  return crossing;
}

template <typename T>
subarray_t<T> find_max_subarray(const vector<T> &a) {
  return find_max_subarray(a, 0, a.size() - 1);
}

template <typename T>
subarray_t<T> find_max_subarray_brute(const vector<T> &a, size_t beg, size_t end) {
  subarray_t<T> max = { beg, beg, a[beg] };
  for (size_t i = beg; i <= end; ++i) {
    T sum = 0;
    for (size_t j = i; j <= end; ++j) {
      sum += a[j];
      if (sum > max.sum)
        max = { i, j, sum };
    }
  }
  return max;
}

template <typename T>
subarray_t<T> find_max_subarray_brute(const vector<T> &a) {
  return find_max_subarray_brute(a, 0, a.size() - 1);
}

template <typename T>
subarray_t<T> find_max_subarray_linear(const vector<T> &a) {
  size_t beg = 0, end = 0;
  T w = a[0], max_sum = a[0];
  for (size_t i = 1; i < a.size(); ++i) {
    if (a[i] > w + a[i]) { // can be simplifed to `if (w < 0)' but retains meaning now
      beg = end = i;
      w = a[i];
    } else
      w += a[i];
    if (w > max_sum) {
      max_sum = w;
      end = i;
    }
  }
  return { beg, end, max_sum };
}

// 6.4 heapsort
size_t parent(size_t i) {
  return i / 2;
}

size_t left(size_t i) {
  return 2 * i;
}

size_t right(size_t i) {
  return 2 * i + 1;
}

template <typename T>
void max_heapify_rec(vector<T> &a, size_t heap_size, size_t i) {
  size_t l = left(i), r = right(i)
    , largest = (l < heap_size && a[l] > a[i]) ? l : i;
  if (r < heap_size && a[r] > a[largest])
    largest = r;
  if (largest != i) {
    std::swap(a[i], a[largest]);
    max_heapify_rec(a, heap_size, largest);
  }
}

template <typename T>
void max_heapify(vector<T> &a, size_t heap_size, size_t i) {
  while (i < heap_size) {
    size_t l = left(i), r = right(i)
      , largest = (l < heap_size && a[l] > a[i]) ? l : i;
    if (r < heap_size && a[r] > a[largest])
      largest = r;
    if (largest == i)
      break;
    std::swap(a[i], a[largest]);
    i = largest;
  }
}

template <typename T>
void min_heapify(vector<T> &a, size_t heap_size, size_t i) {
  while (i < heap_size) {
    size_t l = left(i), r = right(i)
      , smallest = (l < heap_size && a[l] < a[i]) ? l : i;
    if (r < heap_size && a[r] < a[smallest])
      smallest = r;
    if (smallest == i)
      break;
    std::swap(a[i], a[smallest]);
    i = smallest;
  }
}

template <typename T>
size_t build_max_heap(vector<T> &a) {
  size_t heap_size = a.size();
  for (int i = heap_size / 2; i >= 0; --i)
    max_heapify(a, heap_size, i);
  return heap_size;
}

template <typename T>
size_t build_min_heap(vector<T> &a) {
  size_t heap_size = a.size();
  for (int i = heap_size / 2; i >= 0; --i)
    min_heapify(a, heap_size, i);
  return heap_size;
}

template <typename T>
void heapsort(vector<T> &a) {
  size_t heap_size = build_max_heap(a);
  for (size_t i = a.size() - 1; i >= 1; --i) {
    std::swap(a[0], a[i]);
    --heap_size;
    max_heapify(a, heap_size, 0);
  }
}

// max-priority queue algorithms

template <typename T>
T heap_maximum(const vector<T> &a) {
  return a[0];
}

template <typename T>
T heap_extract_max(vector<T> &a, size_t &heap_size) {
  if (heap_size < 1)
    throw;
  T max = a[0];
  a[0] = a[heap_size - 1];
  --heap_size;
  max_heapify(a, 0);
  return max;
}

template <typename T>
void heap_increase_key(vector<T> &a, size_t i, T key) {
  if (key < a[i])
    throw;
  a[i] = key;
  while (i > 0 && a[parent(i)] < a[i]) {
    std::swap(a[i], a[parent(i)]);
    i = parent(i);
  }
}

template <typename T>
size_t max_heap_insert(vector<T> &a, size_t heap_size, T key) {
  ++heap_size;
  size_t i = heap_size - 1;
  a.push_back(key);
  while (i > 0 && a[parent(i)] < a[i]) {
    std::swap(a[i], a[parent(i)]);
    i = parent(i);
  }
  return heap_size;
}

// min-priority queue algorithms

template <typename T>
T heap_minimum(const vector<T> &a) {
  return a[0];
}

template <typename T>
T heap_extract_min(vector<T> &a, size_t &heap_size) {
  if (heap_size < 1)
    throw;
  T min = a[0];
  a[0] = a[heap_size - 1];
  --heap_size;
  min_heapify(a, 0);
  return min;
}

template <typename T>
void heap_decrease_key(vector<T> &a, size_t i, T key) {
  if (key > a[i])
    throw;
  a[i] = key;
  while (i > 0 && a[parent(i)] > a[i]) {
    std::swap(a[i], a[parent(i)]);
    i = parent(i);
  }
}

template <typename T>
size_t min_heap_insert(vector<T> &a, size_t heap_size, T key) {
  ++heap_size;
  size_t i = heap_size - 1;
  a.push_back(key);
  while (i > 0 && a[parent(i)] > a[i]) {
    std::swap(a[i], a[parent(i)]);
    i = parent(i);
  }
  return heap_size;
}

// 7.1 quicksort
template <typename T>
size_t partition_lomuto(std::vector<T> &a, int l, int h) {
  int i = l;
  for (int j = l; j <= h - 1; ++j)
    if (a[j] <= a[h])
      std::swap(a[i++], a[j]);
  std::swap(a[i], a[h]);
  return i;
}

template <typename T>
void quicksort_lomuto(std::vector<T> &a, int l, int h) {
  if (l < h) {
    int m = partition_lomuto(a, l, h);
    quicksort_lomuto(a, l, m - 1);
    quicksort_lomuto(a, m + 1, h);
  }
}

template <typename T>
void quicksort_lomuto(std::vector<T> &a) {
  quicksort_lomuto(a, 0, a.size() - 1);
}

template <typename T>
int partition_hoare(std::vector<T> &a, int l, int h) {
  int i = l - 1, j = h + 1;
  while (1) {
    do {
      --j;
    } while (!(a[j] <= a[l]));
    do {
      i++;
    } while (!(a[i] >= a[l]));
    if (i < j)
      std::swap(a[i], a[j]);
    else
      return j;
  }
}

template <typename T>
void quicksort_hoare(std::vector<T> &a, int l, int h) {
  if (l < h) {
    int m = partition_hoare(a, l, h);
    quicksort_hoare(a, l, m);
    quicksort_hoare(a, m + 1, h);
  }
}

template <typename T>
void quicksort_hoare(std::vector<T> &a) {
  quicksort_hoare(a, 0, a.size() - 1);
}

// 8.2 counting sort
template <typename T>
void counting_sort(std::vector<T> &a, int k) {
  std::vector<T> output(a.size());
  std::vector<int> c(k + 1, 0);
  for (size_t i = 0; i < a.size(); ++i)
    ++c[a[i]];
  for (int i = 1; i <= k; ++i)
    c[i] += c[i - 1];
  for (int i = a.size() - 1; i >= 0; --i) {
    output[c[a[i]] - 1] = a[i];
    --c[a[i]];
  }
  a = output;
}

template <typename T>
void counting_sort(std::vector<T> &a) {
  counting_sort(a, vector_max(a));
}

// 8.3 radix sort
template <typename T>
void radix_sort(std::vector<T> &a) {
  const T max = vector_max(a);

  std::vector<T> b(a.size());
  int c[10];

  for (int d = 1; max / d > 0; d *= 10) {
    for (size_t i = 0; i < 10; ++i)
      c[i] = 0;
    for (size_t i = 0; i < a.size(); i++)
      c[(a[i] / d) % 10]++;
    for (int i = 1; i < 10; i++)
      c[i] += c[i - 1];
    for (int i = a.size() - 1; i >= 0; i--) {
      T x = (a[i] / d) % 10;
      b[c[x] - 1] = a[i];
      c[x]--;
    }
    a = b;
  }
}

// 9.3 select
template <typename T>
T median5(std::vector<T> &a, size_t l, size_t h) {
  for (size_t j = l; j <= h; ++j) {
    T key = a[j - 1];
    size_t i = j - 1;
    while (i >= l && key < a[i - 1]) {
      a[i] = a[i - 1];
      --i;
    }
    a[i] = key;
  }
  size_t n = h - l + 1;
  return n % 2 == 0 ? a[l + n / 2 - 2] : a[l + n / 2 - 1];
}

template <typename T>
T select(std::vector<T> &a, size_t l, size_t h, size_t i) {
  size_t n = h - l + 1, j;
  std::vector<T> medians((n + 4) / 5);
  for (j = 1; j <= n / 5; ++j)
    medians[j - 1] = median5(a, l + (j - 1) * 5, l + (j - 1) * 5 + 4);
  if (n % 5 != 0)
    medians[j - 1] = median5(a, l + (j - 1) * 5, l + (j - 1) * 5 + n % 5 - 1);

  T x = medians.size() == 1 ? medians[0]
    : select(medians, 1, medians.size(), medians.size() / 2);

  size_t k = 0;
  for (size_t j = l, m = l; j <= h; ++j)
    if (a[j - 1] <= x) {
      std::swap(a[m++ - 1], a[j - 1]);
      ++k;
    }

  if (i == k)
    return x;
  else if (i < k)
    return select(a, l, l + k - 1, i);
  else
    return select(a, l + k, h, i - k);
}

template <typename T>
T select(std::vector<T> a, size_t i) {
  return select(a, 1, a.size(), i);
}

// BST
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

// trie
struct trie_t {
  map<char, trie_t> children;
  string value;
  bool end;

  explicit trie_t(const string &val = "") : value(val), end(false) {}

  void add(char);
  bool find(const string &);
  void insert(const string &);
  vector<string> all_prefixes();
  vector<string> autocomplete(const string &);
  bool can_find_unambigously(const string &prefix, const string &word);
};

void trie_t::add(char c) {
  if (value == "")
    children[c] = trie_t(string(1, c));
  else
    children[c] = trie_t(value + c);
}

bool trie_t::find(const string &word) {
  trie_t *node = this;
  for (size_t i = 0; i < word.length(); ++i) {
    char c = word[i];
    if (node->children.find(c) == node->children.end())
      return false;
    node = &node->children[c];
  }
  return node->end;
}

void trie_t::insert(const string &word) {
  trie_t *node = this;
  for (size_t i = 0; i < word.length(); ++i) {
    char c = word[i];
    if (node->children.find(c) == node->children.end())
      node->add(c);
    node = &node->children[c];
  }
  node->end = true;
}

vector<string> trie_t::all_prefixes() {
  vector<string> results;
  if (end)
    results.push_back(value);

  if (children.size())
    for (auto iter = children.begin(); iter != children.end(); ++iter) {
      vector<string> nodes = iter->second.all_prefixes();
      results.insert(results.end(), nodes.begin(), nodes.end());
    }

  return results;
}

vector<string> trie_t::autocomplete(const string &prefix) {
  trie_t *node = this;
  vector<string> results;
  for (size_t i = 0; i < prefix.length(); ++i) {
    char c = prefix[i];
    if (node->children.find(c) == node->children.end())
      return results;
    else
      node = &node->children[c];
  }
  return node->all_prefixes();
}

bool trie_t::can_find_unambigously(const string &prefix, const string &word) {
  vector<string> results = autocomplete(prefix);
  return (results.size() == 1 && results[0] == word);
}

// 15.1 rod cutting
int rod_cutting1(const v& p, int n) {
  if (n == 0)
    return 0;
  int max_cost = p[n - 1];
  for (int i = 1; i < n; ++i)
    max_cost = max(max_cost, rod_cutting1(p, i) + rod_cutting1(p, n - i));
  return max_cost;
}

int rod_cutting2(v p, int n) {
  if (n == 0)
    return 0;
  int max_cost = neginf;
  for (int i = 0; i < n; ++i)
    max_cost = max(max_cost, p[i] + rod_cutting2(p, n - i - 1));
  return max_cost;
}

static int rod_cutting3_aux(v &memo, v p, int n) {
  if (memo[n] >= 0)
    return memo[n];
  if (n == 0) {
    memo[n] = 0;
    return 0;
  }
  int max_cost = neginf;
  for (int i = 1; i <= n; ++i)
    max_cost = max(max_cost, p[i - 1] + rod_cutting3_aux(memo, p, n - i));
  memo[n] = max_cost;
  return max_cost;
}

int rod_cutting3(const v& p, int n) {
  v memo(n + 1, neginf);
  return rod_cutting3_aux(memo, p, n);
}

int rod_cutting4(v p, int n) {
  v memo(n + 1);
  memo[0] = 0;
  for (int j = 1; j <= n; ++j) {
    int max_cost = neginf;
    for (int i = 1; i <= j; ++i)
      max_cost = max(max_cost, p[i - 1] + memo[j - i]);
    memo[j] = max_cost;
  }
  return memo[n];
}

