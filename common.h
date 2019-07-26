#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

const int neginf = INT_MIN;

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

int max(int x, int y)
{
    return x > y ? x : y;
}

void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

void sneed()
{
    srand(time(NULL));
}

int rand_in_range(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int is_sorted(const int *a, int len)
{
    int prev = a[0];

    for (int i = 1; i < len; ++i)
        if (prev > a[i])
            return 0;

    return 1;
}

