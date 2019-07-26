#pragma once

#include "common.h"

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

