#pragma once

#include "common.h"

void radix_sort(int *a, int len)
{
    const int max = array_max(a, len);
    int b[len], c[10];

    for (int d = 1; max / d > 0; d *= 10) {
        int_bzero(c, 10);

        for (int i = 0; i < len; ++i)
            c[(a[i] / d) % 10]++;

        for (int i = 1; i < 10; ++i)
            c[i] += c[i - 1];

        for (int i = len - 1; i >= 0; --i) {
            int x = (a[i] / d) % 10;

            b[c[x] - 1] = a[i];
            --c[x];
        }

        memcpy(a, b, len);
    }
}

