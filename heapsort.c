#include <stdio.h>

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
    int lc, rc, largest, t;

    while (i < h) {
        lc = left_child(i);
        rc = right_child(i);

        largest = (lc < h && a[lc] > a[i]) ? lc : i;

        if (rc < h && a[rc] > a[largest])
            largest = rc;

        if (largest == i)
            break;

        t = a[i];
        a[i] = a[largest];
        a[largest] = t;

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
        *(volatile int*)0 = 1;

    int max = a[0];
    a[0] = a[*h - 1];
    *h = *h - 1;

    maintain_heap_prop_for_element(a, n, 0);

    return max;
}

void heap_increase_key(int *a, int i, int key)
{
    int t;

    if (key < a[i])
        *(volatile int*)0 = 1;

    a[i] = key;

    while (i > 0 && a[parent(i)] < a[i]) {
        t = a[i];
        a[i] = a[parent(i)];
        a[parent(i)] = t;

        i = parent(i);
    }
}

void max_heap_insert(int *a, int *h, int key)
{
    int i, t;

    *h = *h + 1;

    i = *h - 1;

    a[i] = key;

    while (i > 0 && a[parent(i)] < a[i]) {
        t = a[i];
        a[i] = a[parent(i)];
        a[parent(i)] = t;

        i = parent(i);
    }
}

void heapsort(int *a, int n)
{
    int heap_size = n, t;

    build_max_heap(a, n);

    puts("max heap:");
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    puts("");

    for (int i = n - 1; i >= 1; --i) {
        t = a[0];
        a[0] = a[i];
        a[i] = t;

        --heap_size;
        maintain_heap_prop_for_element(a, heap_size, 0);
    }
}

int main() {
    int a[] = { 5, 10, 2, 3, 7, 1, 6 };
    int n = sizeof(a) / sizeof(*a);

    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    puts("");

    heapsort(a, n);

    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    puts("");
}
