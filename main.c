#include <stdio.h>
#include <stdlib.h>
#include "heapsort.h"

int main()
{
    int testcases = 1000, arraylen = 500, rangemin = -500, rangemax = 500;
    sneed();

    for (int i = 0; i < testcases; ++i) {
        int a[arraylen];

        for (int j = 0; j < arraylen; ++j)
            a[j] = rand_in_range(rangemin, rangemax);

        heapsort(a, arraylen);

        if (!is_sorted(a, arraylen))
            die("panic");
    }
}

