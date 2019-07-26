#include "util.h"

int max_subarray_crossing_midpoint(int *p, int l, int m, int h)
{
    int i, s, left_sum = neginf, right_sum = neginf;

    for (i = m, s = 0; i >= l; --i) {
        s += p[i - 1];
        left_sum = max(left_sum, s);
    }

    for (i = m + 1, s = 0; i <= h; ++i) {
        s += p[i - 1];
        right_sum = max(right_sum, s);
    }

    return left_sum + right_sum;
}

int max_subarray(int *p, int l, int h)
{
    int m, left_sum, cross_sum, right_sum;

    if (l == h) {
        return p[l - 1];
    }

    m = (l + h) / 2;

    left_sum = max_subarray(p, l, m);
    right_sum = max_subarray(p, m + 1, h);
    cross_sum = max_subarray_crossing_midpoint(p, l, m, h);

    return max(left_sum, max(cross_sum, right_sum));
}

int main() {
    int p[] = { 100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97 };
    int n = sizeof(p) / sizeof(*p);
    int d[n - 1];

    for (int i = 0; i < n - 1; ++i) {
        d[i] = p[i + 1] - p[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        printf("%d ", d[i]);
    }
    puts("");

    printf("max_subarray(d, n - 1)=%d\n", max_subarray(d, 1, n - 1));
}

