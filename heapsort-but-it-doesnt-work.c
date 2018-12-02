#include "util.h"

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

/* 1-based idx */
void maintain_heap_for_element(int *a, int l, int i)
{
    int lc = left_child(i), rc = right_child(i), largest, t;

    largest = (lc < l && a[lc - 1] > a[i - 1]) ? lc : i;

    if (rc < l && a[rc - 1] > a[largest - 1])
        largest = rc;

    if (largest != i) {
        t = a[i - 1];
        a[i - 1] = a[largest - 1];
        a[largest - 1] = t;

        maintain_heap_for_element(a, l, largest);
    }
}

void build_max_heap(int *a, int n)
{
    for (int i = n / 2; i >= 1; --i)
        maintain_heap_for_element(a, n, i);
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

    for (int i = n; i >= 2; --i) {
        t = a[0];
        a[0] = a[i - 1];
        a[i - 1] = t;
        --heap_size;
        maintain_heap_for_element(a, heap_size, 1);
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

