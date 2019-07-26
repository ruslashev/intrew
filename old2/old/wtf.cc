#include <iostream>
#include <vector>

using namespace std;

unsigned long long timer(int *arr, int arrSize) {
  union ticks {
    unsigned long long t64;
    struct s32 {
      long th, tl;
    } t32;
  } start, end;
  unsigned long long tmp = -1;
  for (int j = 0; j < 10; ++j) {
    asm("rdtsc\n" : "=a"(start.t32.th), "=d"(start.t32.tl));
    for (int i = 0, index = 0; i < arrSize; ++i)
      index = arr[index];
    asm("rdtsc\n" : "=a"(end.t32.th), "=d"(end.t32.tl));
    tmp = end.t64 - start.t64;
  }
  return tmp / arrSize;
}

int main() {
  const int cacheSize = 1048576, intz = cacheSize / sizeof(int);
  for(int f = 1; f < 32; ++f) {
    const int elemCount = intz / f;
    const int arrSize = intz * f;
    printf("arrSize=%d\n", arrSize);
    int *arr = new int[arrSize];
    for (int i = 0; i < f; ++i)
      for (int j = 0; j < elemCount; ++j)
        arr[i * intz + j] = (i + 1) * intz + j;
    for (int j = 0; j < elemCount; ++j)
      arr[(f - 1) * intz + j] = j + 1;
    arr[(f - 1) * (intz - 1)] = 0;

    cout << timer(arr, arrSize) << ", ";
    delete[] arr;
  }
  std::cout << std::endl;
}

