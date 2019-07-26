#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "merge-sort.h"

void sneed()
{
    srand(time(NULL));
}

int rand_in_range(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int sorted(int *a, int len)
{
    int prev = a[0];

    for (int i = 1; i < len; ++i)
        if (prev > a[i])
            return 0;

    return 1;
}

#define die(...) do { printf(__VA_ARGS__); puts(""); exit(1); } while (0)

int main()
{
    int testcases = 1000, arraylen = 500, rangemin = -500, rangemax = 500;
    sneed();

    for (int i = 0; i < testcases; ++i) {
        int a[arraylen];

        for (int j = 0; j < arraylen; ++j)
            a[j] = rand_in_range(rangemin, rangemax);

        merge_sort(a, arraylen);

        if (!sorted(a, arraylen))
            die("panic");
    }
}

