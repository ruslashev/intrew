#pragma once

#include "common.h"

typedef struct
{
    int value;
} item;

typedef struct
{
    int size;
    item *data;
} heap;

int item_has_less_priority_exp(const item *x, const item *y)
{
    return x->value < y->value;
}

int item_has_less_priority(heap *h, int xidx, int yidx)
{
    return item_has_less_priority_exp(&h->data[xidx], &h->data[yidx]);
}

void item_swap(item *x, item *y)
{
    item t;

    t.value = x->value;
    x->value = y->value;
    y->value = t.value;
}

void heap_init(heap *h, item *storage)
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

        highest_priority = (l < h->size && item_has_less_priority(h, i, l)) ? l : i;

        if (r < h->size && item_has_less_priority(h, highest_priority, r))
            highest_priority = r;

        if (highest_priority == i)
            break;

        item_swap(&h->data[i], &h->data[highest_priority]);

        i = highest_priority;
    }
}

void heap_sift_up(heap *h, int i)
{
    while (i > 0 && item_has_less_priority(h, heap_parent(i), i)) {
        item_swap(&h->data[i], &h->data[heap_parent(i)]);

        i = heap_parent(i);
    }
}

void heap_increse_key_priority(heap *h, int i, int newvalue)
{
    h->data[i].value = newvalue;

    heap_sift_up(h, i);
}

void heap_insert(heap *h, int value)
{
    ++h->size;

    heap_increse_key_priority(h, h->size - 1, value);
}

void heap_remove(heap *h, int idx)
{
    h->data[idx] = h->data[h->size - 1];
    --h->size;

    if (idx == 0) {
        heap_sift_down(h, idx);
        return;
    }

    if (item_has_less_priority(h, heap_parent(idx), idx))
        heap_sift_up(h, idx);
    else
        heap_sift_down(h, idx);
}

#if 0
void heap_create(int *a, int n)
{
    for (int i = n / 2; i >= 0; --i)
        heap_sift_down(a, n, i);
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
#endif

