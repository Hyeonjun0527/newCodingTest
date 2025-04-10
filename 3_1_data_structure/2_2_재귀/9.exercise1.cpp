#include <stdio.h>
#include <time.h>

// 반복적인 방법
double power_iterative(double x, int n)
{
    double result = 1.0;
    for (int i = 0; i < n; i++)
    {
        result *= x;
    }
    return result;
}

// 재귀적인방법
double power_recursive(double x, int n)
{
    if (n == 0)
    {
        return 1.0;
    }
    return x * power_recursive(x, n - 1);
}

int main()
{
    clock_t start, end;
    start = clock();
    // double a = 0;
    for (int i = 0; i < 10000; i++)
    {
        power_iterative(2, i);
    }
    end = clock();
    // printf("%e\n", a);
    printf("The power_iterative took %f seconds.\n",
           ((double)end - start) / CLOCKS_PER_SEC);
    // do for other functions

    clock_t s, e;
    s = clock();
    // double b = 0;
    for (int i = 0; i < 10000; i++)
    {
        power_recursive(2, i);
    }
    e = clock();
    // printf("%e\n", b);
    printf("The power_recursive took %f seconds.\n",
           ((double)e - s) / CLOCKS_PER_SEC);
    // do for other functions
    return 0;
}
