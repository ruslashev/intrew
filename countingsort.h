#pragma once

#include "common.h"

static void counting_sort_aux(int *a, int len, int min, int max)
{
    int range = max - min + 1, c[range];

    int_bzero(c, range);

    for (int i = 0; i < len; i++)
        ++c[a[i] - min];

    for (int i = min, z = 0; i <= max; ++i)
        for (int j = 0; j < c[i - min]; ++j)
            a[z++] = i;
}

static void find_min_max(int *a, int len, int *min, int *max)
{
    *min = *max = a[0];

    for (int i = 1; i < len; ++i) {
        if (a[i] < *min)
            *min = a[i];

        if (a[i] > *max)
            *max = a[i];
    }
}

void counting_sort(int *a, int len)
{
    int min, max;

    find_min_max(a, len, &min, &max);

    counting_sort_aux(a, len, min, max);
}

static void counting_sort2_aux(int *a, int n, int max_el)
{
    int c[max_el + 1],
        output[n + 1];

    int_bzero(c, max_el + 1);

    for (int i = 0; i < n; ++i)
        c[a[i]]++;

    for (int i = 1; i <= max_el; ++i)
        c[i] += c[i - 1];

    for (int i = n - 1; i >= 0; --i) {
        output[c[a[i]]] = a[i];
        c[a[i]]--;
    }

    for (int i = 0; i < n; ++i)
        a[i] = output[i + 1];
}

void counting_sort2(int *a, int n)
{
    counting_sort_aux(a, n, array_max(a, n));
}

