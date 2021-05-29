#include <stdio.h>
#include <stdlib.h>
#include "radixsort.h"

int main()
{
    int testcases = 1, arraylen = 10, rangemin = 100, rangemax = 999;

    sneed();

    for (int i = 0; i < testcases; ++i) {
        int a[arraylen];

        printf("testcase %d\n", i);

        for (int j = 0; j < arraylen; ++j)
            a[j] = rand_in_range(rangemin, rangemax);

        print_array(a, arraylen);

        radix_sort(a, arraylen);

        print_array(a, arraylen);

        if (!is_sorted(a, arraylen))
            die("panic");
    }
}

