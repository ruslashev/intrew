#### common.h

``` c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

const int neginf = INT_MIN, inf = INT_MAX;

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

int max(int x, int y)
{
    return x > y ? x : y;
}

void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

void sneed()
{
    srand(time(NULL));
}

int rand_in_range(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int is_sorted(const int *a, int len)
{
    int prev = a[0];

    for (int i = 1; i < len; ++i)
        if (prev > a[i])
            return 0;

    return 1;
}

void int_bzero(int *a, int len)
{
    memset(a, 0, len * sizeof(int));
}

int array_max(const int *a, int len)
{
    int t = a[0];

    for (int i = 1; i < len; ++i)
        t = max(t, a[i]);

    return t;
}
```

#### 2.1 insertion sort

``` c
void insertion_sort(int *a, int len)
{
    for (int i = 1; i < len; ++i) {
        const int key = a[i];
        int j = i - 1;
        for (; j >= 0 && a[j] > key; --j)
            a[j + 1] = a[j];
        a[j + 1] = key;
    }
}
```

#### 2.3.1 merge sort

``` c
void merge(int *a, int l, int m, int h)
{
    int ll = m - l + 1, rl = h - m;
    int left[ll], right[rl];
    int i = 0, j = 0, k = l;

    for (int i = 0; i < ll; ++i)
        left[i] = a[l + i];

    for (int i = 0; i < rl; ++i)
        right[i] = a[m + i + 1];

    for (; i < ll && j < rl; ++k)
        a[k] = (left[i] <= right[j]) ? left[i++] : right[j++];

    for (; i != ll; ++k, ++i)
        a[k] = left[i];

    for (; j != rl; ++k, ++j)
        a[k] = right[j];
}

void merge_sort_aux(int *a, int l, int h)
{
    int m = (l + h) / 2;

    if (h - l < 1)
        return;

    merge_sort_aux(a, l, m);
    merge_sort_aux(a, m + 1, h);
    merge(a, l, m, h);
}

void merge_sort(int *a, int len)
{
    merge_sort_aux(a, 0, len - 1);
}
```

#### 4.1 maximum subarray

``` c
struct subarray
{
    int start, end, sum;
};

int max_subarray_crossing_midpoint(int *a, int l, int m, int h)
{
    int i, s, left_sum = neginf, right_sum = neginf;

    for (i = m, s = 0; i >= l; --i) {
        s += a[i - 1];
        left_sum = max(left_sum, s);
    }

    for (i = m + 1, s = 0; i <= h; ++i) {
        s += a[i - 1];
        right_sum = max(right_sum, s);
    }

    return left_sum + right_sum;
}

int max_subarray(int *a, int l, int h)
{
    int m, left_sum, cross_sum, right_sum;

    if (l == h)
        return a[l - 1];

    m = (l + h) / 2;

    left_sum = max_subarray(a, l, m);
    right_sum = max_subarray(a, m + 1, h);
    cross_sum = max_subarray_crossing_midpoint(a, l, m, h);

    return max(left_sum, max(cross_sum, right_sum));
}

struct subarray max_subarray_linear(int *a, int len)
{
    int beg = 0, end = 0;
    int w = a[0], max_sum = a[0];

    for (int i = 1; i < len; ++i) {
        if (a[i] > w + a[i]) {
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
```

#### heapsort and priority queue

``` c
typedef struct
{
    int size;
    int *data;
} heap;

int element_has_less_priority_exp(int x, int y)
{
    return x < y;
}

int element_has_less_priority(heap *h, int xidx, int yidx)
{
    return element_has_less_priority_exp(h->data[xidx], h->data[yidx]);
}

void element_swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

void heap_init(heap *h, range *storage)
{
    h->size = 0;
    h->data = storage;
}

int heap_parent(int idx)
{
    return idx / 2;
}

int heap_left_child(int idx)
{
    return 2 * idx;
}

int heap_right_child(int idx)
{
    return 2 * idx + 1;
}

void heap_sift_down(heap *h, int i)
{
    int l, r, highest_priority;

    while (i < h->size) {
        l = heap_left_child(i);
        r = heap_right_child(i);

        highest_priority = (l < h->size && element_has_less_priority(h, i, l)) ? l : i;

        if (r < h->size && element_has_less_priority(h, highest_priority, r))
            highest_priority = r;

        if (highest_priority == i)
            break;

        element_swap(&h->data[i], &h->data[highest_priority]);

        i = highest_priority;
    }
}

void heap_sift_up(heap *h, int i)
{
    while (i > 0 && range_has_less_priority(h, heap_parent(i), i)) {
        range_swap(&h->data[i], &h->data[heap_parent(i)]);

        i = heap_parent(i);
    }
}

void heap_build(int *a, int n)
{
    for (int i = n / 2; i >= 0; --i)
        heap_sift_down(a, n, i);
}

void heap_increse_key_priority(heap *h, int i, int a)
{
    h->data[i] = a;

    heap_sift_up(h, i);
}

void heap_insert(heap *h, int a)
{
    ++h->size;

    heap_increse_key_priority(h, h->size - 1, a);
}

void heap_remove(heap *h, int idx)
{
    h->data[idx] = h->data[h->size - 1];
    --h->size;

    if (idx == 0) {
        heap_sift_down(h, idx);
        return;
    }

    if (element_has_less_priority(h, heap_parent(idx), idx))
        heap_sift_up(h, idx);
    else
        heap_sift_down(h, idx);
}

void heap_extract_max(heap *h, range *r)
{
    if (h->size < 1)
        return;

    r->a = h->data[0].a;
    r->b = h->data[0].b;

    heap_remove(h, 0);
}

void heapsort(int *a, int n)
{
    int heap_size = n;

    heap_build(a, n);

    for (int i = n - 1; i >= 1; --i) {
        swap(&a[0], &a[i]);

        --heap_size;
        maintain_heap_prop_for_element(a, heap_size, 0);
    }
}
```

#### quicksort

``` c
int partition(int *a, int l, int h)
{
    int pivot = a[l], i = l - 1, j = h + 1, t;

    while (1) {
        do {
            ++i;
        } while (a[i] < pivot);

        do {
            --j;
        } while (a[j] > pivot);

        if (i >= j)
            return j;

        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}

void quicksort(int *a, int l, int h)
{
    if (l >= h)
        return;

    int m = partition(a, l, h);

    quicksort(a, l, m);
    quicksort(a, m + 1, h);
}

void quicksort_full(int *a, int len)
{
    quicksort(a, 0, len - 1);
}
```

#### counting sort

``` c
void counting_sort_aux(int *a, int len, int max_el)
{
    int c[max_el + 1],
        output[len + 1];

    int_bzero(c, max_el + 1);

    for (int i = 0; i < len; ++i)
        c[a[i]]++;

    for (int i = 1; i <= max_el; ++i)
        c[i] += c[i - 1];

    for (int i = len - 1; i >= 0; --i) {
        output[c[a[i]]] = a[i];
        c[a[i]]--;
    }

    for (int i = 0; i < len; ++i)
        a[i] = output[i + 1];
}

void counting_sort(int *a, int len)
{
    counting_sort_aux(a, len, array_max(a, len));
}
```

#### avl tree

``` c
struct avl_node_t
{
    int key;
    void *data;

    size_t height;
    struct avl_node_t *left, *right;
};

struct avl_tree_t
{
    struct avl_node_t *root;
};

static void construct_avl_node(struct avl_node_t *node, int key, void *data)
{
    node->key = key;
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
}

#define min(a, b) \
({ \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; \
})

#define max(a, b) \
({ \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; \
})

static size_t height(struct avl_node_t *x)
{
    return x != NULL ? x->height : 0;
}

static int diff(struct avl_node_t *x)
{
    return height(x->right) - height(x->left);
}

static struct avl_node_t* right_rotate(struct avl_node_t *x)
{
    struct avl_node_t *y = x->left;

    x->left = y->right;

    y->right = x;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

static struct avl_node_t* left_rotate(struct avl_node_t *x)
{
    struct avl_node_t *y = x->right;

    x->right = y->left;

    y->left = x;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

static struct avl_node_t* balance(struct avl_node_t *x)
{
    x->height = max(height(x->left), height(x->right)) + 1;

    if (diff(x) >= 2) {
        if (diff(x->right) < 0) {
            x->right = right_rotate(x->right);
        }

        return left_rotate(x);
    } else if (diff(x) <= -2) {
        if (diff(x->left) > 0) {
            x->left = left_rotate(x->left);
        }

        return right_rotate(x);
    }

    return x;
}

static struct avl_node_t* insert(struct avl_node_t *x, int key, void *data)
{
    struct avl_node_t *new;

    if (x == NULL) {
        new = malloc(sizeof(struct avl_node_t));
        construct_avl_node(new, key, data);
        return new;
    }

    if (key < x->key) {
        x->left = insert(x->left, key, data);
    } else {
        x->right = insert(x->right, key, data);
    }

    return balance(x);
}

static struct avl_node_t* min_node(struct avl_node_t *x)
{
    return x->left != NULL ? min_node(x->left) : x;
}

static struct avl_node_t* delete_min(struct avl_node_t *x)
{
    if (x->left == NULL) {
        return x->right;
    }

    x->left = delete_min(x->left);

    return balance(x);
}

static struct avl_node_t* delete_key(struct avl_node_t *x, int key)
{
    struct avl_node_t *l, *r, *m;

    if (x == NULL) {
        return NULL;
    }

    if (key < x->key) {
        x->left = delete_key(x->left, key);
    } else if (key > x->key) {
        x->right = delete_key(x->right, key);
    } else {
        l = x->left;
        r = x->right;

        free(x);

        if (r == NULL) {
            return l;
        }

        m = min_node(r);
        m->right = delete_min(r);
        m->left = l;

        return balance(m);
    }

    return balance(x);
}

static void* find(struct avl_node_t *root, int key)
{
    if (root == NULL) {
        return NULL;
    }

    if (key < root->key) {
        return find(root->left, key);
    }

    if (key == root->key) {
        return root->data;
    }

    return find(root->right, key);
}

static void destruct(struct avl_node_t *node, void (*node_destruct_cb)(struct avl_node_t*))
{
    if (node == NULL) {
        return;
    }

    destruct(node->left, node_destruct_cb);
    destruct(node->right, node_destruct_cb);

    if (node_destruct_cb != NULL)
        node_destruct_cb(node);

    free(node);
}

void avl_tree_construct(struct avl_tree_t *tree)
{
    tree->root = NULL;
}

void avl_tree_destruct(struct avl_tree_t *tree, void (*node_destruct_cb)(struct avl_node_t*))
{
    destruct(tree->root, node_destruct_cb);
}

void avl_tree_insert(struct avl_tree_t *tree, int key, void *data)
{
    tree->root = insert(tree->root, key, data);
}

void avl_tree_delete(struct avl_tree_t *tree, int key)
{
    tree->root = delete_key(tree->root, key);
}

void* avl_tree_find(struct avl_tree_t *tree, int key)
{
    return find(tree->root, key);
}
```

#### always sorted array

``` c
int a[max];
int len = 0;

void add(int x)
{
    int i;

    for (i = len - 1; i >= 0 && a[i] > x; i--)
        a[i + 1] = a[i];

    a[i + 1] = x;

    ++len;
}

int bsearch(int l, int h, int key)
{
    if (h < l)
        return -1;

    int mid = l + (h - l) / 2;

    if (key == a[mid])
        return mid;

    if (key > a[mid])
        return bsearch(mid + 1, h, key);

    return bsearch(l, mid - 1, key);
}

void delete(int x)
{
    int pos = bsearch(0, len - 1, x);

    if (pos == -1)
        return;

    for (int i = pos; i < len - 1; i++)
        a[i] = a[i + 1];

    --len;
}
```

