#include <stdio.h>
#include <stdlib.h>
#include "radixsort.h"

int main()
{
    int testcases = 1, arraylen = 5, rangemin = 10, rangemax = 99;

    sneed();

    for (int i = 0; i < testcases; ++i) {
        int a[arraylen];

        printf("testcase %d\n", i);

        for (int j = 0; j < arraylen; ++j)
            a[j] = rand_in_range(rangemin, rangemax);

        for (int j = 0; j < arraylen; ++j)
            printf("%d ", a[j]);
        printf("\n");

        radix_sort(a, arraylen);

        for (int j = 0; j < arraylen; ++j)
            printf("%d ", a[j]);
        printf("\n");

        if (!is_sorted(a, arraylen))
            die("panic");
    }
}

