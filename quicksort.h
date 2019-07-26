#pragma once

#include "common.h"

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

