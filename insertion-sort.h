#pragma once

void insertion_sort(int *a, int len)
{
    for (int i = 1; i < len; ++i) {
        const int key = a[i];
        int j = i - 1;
        for (; j >= 0 && a[j] > key; --j)
            a[j + 1] = a[j];
        a[j + 1] = key;
    }
}

