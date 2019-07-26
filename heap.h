#pragma once

#include "common.h"

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

