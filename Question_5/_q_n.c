#include "header.h"
#include <math.h>
void maxsubarray(int seed, int n)
{
    int array[n];
    srand(seed);

    for (int i = 0; i < n; i++)
    {
        array[i] = rand() % 75 - 25;
    }
    int best = 0, sum = 0;
    for (int k = 0; k < n; k++)
    {
        sum = fmax(array[k], sum + array[k]);
        best = fmax(best, sum);
    }
    printf("The best sum is: %d\n", best);
}
