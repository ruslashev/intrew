#pragma once

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int neginf = INT_MIN, inf = INT_MAX;

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

static int max(int x, int y)
{
    return x > y ? x : y;
}

static void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

static void sneed()
{
    srand(time(NULL));
}

static int rand_in_range(int min, int max)
{
    return min + rand() % (max - min + 1);
}

static int is_sorted(const int *a, int len)
{
    for (int i = 0; i < len; ++i)
        for (int j = 0; j < i; ++j)
            if (a[j] >= a[i])
                return 0;

    return 1;
}

static void int_bzero(int *a, int len)
{
    memset(a, 0, len * sizeof(int));
}

static int array_max(const int *a, int len)
{
    int t = a[0];

    for (int i = 1; i < len; ++i)
        t = max(t, a[i]);

    return t;
}

