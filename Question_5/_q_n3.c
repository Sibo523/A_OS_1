#include "header.h"

void maxsubarray(int seed, int n)
{
    int array[n];
    srand(seed);

    for (int i = 0; i < n; i++)
    {
        array[i] = rand() % 75 - 25;
    }
    int best = 0;
    for (int a = 0; a < n; a++)
    {
        for (int b = a; b < n; b++)
        {
            int sum = 0;
            for (int k = a; k <= b; k++)
            {
                sum += array[k];
            }
            best = fmax(best, sum);
        }
    }
    printf("The best sum is: %d\n", best);
} 
