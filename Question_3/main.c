
#include <stdio.h>
#include <stdlib.h>
// #pragma once
#include "targil3.h"
int main()
{
    double array[5][2]= {{2,1}, {2, 10}, {2,2}, {3,3}, {100, 3}};
    for (int i = 0; i < 5; i++) {
        int lambda = array[i][0];
        int k = array[i][1];
        long double result = poi(k,lambda); // there's no real reason why last func was void and now is long double
        printf("Poisson(\"k:\" %i, \"lambda:\" %i) = %Le\n", k, lambda, result);
    }
}