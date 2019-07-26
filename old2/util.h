#pragma once

#include <stdio.h>
#include <limits.h>

static const int neginf = INT_MIN, inf = INT_MAX;

int max(int x, int y)
{
    return (x > y) ? x : y;
}

