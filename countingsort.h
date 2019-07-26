#pragma once

#include "common.h"

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

