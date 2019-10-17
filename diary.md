#### common.h

```
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

```
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

```
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

```
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

```
int parent(int i)
{
    return i / 2;
}

int left_child(int i)
{
    return 2 * i;
}

int right_child(int i)
{
    return 2 * i + 1;
}

void maintain_heap_prop_for_element(int *a, int h, int i)
{
    int lc, rc, largest;

    while (i < h) {
        lc = left_child(i);
        rc = right_child(i);

        largest = (lc < h && a[lc] > a[i]) ? lc : i;

        if (rc < h && a[rc] > a[largest])
            largest = rc;

        if (largest == i)
            break;

        swap(&a[i], &a[largest]);

        i = largest;
    }
}

void build_max_heap(int *a, int n)
{
    for (int i = n / 2; i >= 0; --i)
        maintain_heap_prop_for_element(a, n, i);
}

int heap_maximum(int *a)
{
    return a[0];
}

int heap_extract_max(int *a, int n, int *h)
{
    if (*h < 1)
        die("heap underflow");

    int max = a[0];

    a[0] = a[*h - 1];
    *h = *h - 1;
    maintain_heap_prop_for_element(a, n, 0);

    return max;
}

void heap_increase_key(int *a, int i, int key)
{
    if (key < a[i])
        return;

    a[i] = key;

    while (i > 0 && a[parent(i)] < a[i]) {
        swap(&a[i], &a[parent(i)]);

        i = parent(i);
    }
}

void max_heap_insert(int *a, int *h, int key)
{
    int i;

    *h = *h + 1;

    i = *h - 1;

    a[i] = key;

    while (i > 0 && a[parent(i)] < a[i]) {
        swap(&a[i], &a[parent(i)]);

        i = parent(i);
    }
}

void heapsort(int *a, int n)
{
    int heap_size = n;

    build_max_heap(a, n);

    for (int i = n - 1; i >= 1; --i) {
        swap(&a[0], &a[i]);

        --heap_size;
        maintain_heap_prop_for_element(a, heap_size, 0);
    }
}
```

#### quicksort

```
int partition_hoare(int *a, int l, int h)
{
    int i = l - 1, j = h + 1;

    while (1) {
        do {
            --j;
        } while (!(a[j] <= a[l]));

        do {
            i++;
        } while (!(a[i] >= a[l]));

        if (i < j)
            swap(&a[i], &a[j]);
        else
            return j;
    }
}

void quicksort_hoare(int *a, int l, int h)
{
    if (l >= h)
        return;

    int m = partition_hoare(a, l, h);

    quicksort_hoare(a, l, m);
    quicksort_hoare(a, m + 1, h);
}

void quicksort(int *a, int len)
{
    quicksort_hoare(a, 0, len - 1);
}
```

#### counting sort

```
void counting_sort_aux(int *a, int len, int k)
{
    int output[len], c[k + 1];

    int_bzero(c, k + 1);

    for (int i = 0; i < len; ++i)
        ++c[a[i] - 1];

    for (int i = 0; i < k; ++i)
        c[i] += c[i - 1];

    for (int i = len; i >= 1; --i) {
        output[c[a[i - 1] - 1] - 1] = a[i - 1];
        --c[a[i - 1] - 1];
    }

    memmove(a, output, len);
}

void counting_sort(int *a, int len)
{
    counting_sort_aux(a, len, array_max(a, len));
}
```

