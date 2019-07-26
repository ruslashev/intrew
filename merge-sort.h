#pragma once

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

