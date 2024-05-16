
#include <stdio.h>
#include <stdlib.h>
// #pragma once
#include "targil3.h"
int main()
{
    double array[5][2]= {{2,1}, {2, 10}, {2,2}, {3,3}, {100, 3}};
    for (int i = 0; i < 5; i++) {
        double lambda = array[i][0];
        double k = array[i][1];
        long double result = poi(k,lambda);
        printf("Poisson(%f, %f) = %Lf\n", k, lambda, result);
    }
}