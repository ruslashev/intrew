#include "util.h"

int rodcut(int *p, int n)
{
    int m[n + 1], s;

    m[0] = 0;

    for (int l = 1; l <= n; ++l) {
        s = neginf;
        for (int i = 1; i <= l; ++i) {
            s = max(s, p[i - 1] + m[l - i]);
        }
        m[l] = s;
    }

    return m[n];
}

int main()
{
    int p[] = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
    int n = sizeof(p) / sizeof(*p);

    printf("rodcut(p, n)=%d\n", rodcut(p, n));
}

