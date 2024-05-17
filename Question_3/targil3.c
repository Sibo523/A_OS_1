
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long factorial (int n){ //classing function factorial rec
    if (n == 0){
        return 1;
    }
    return n*factorial(n-1);
}

long double poi(int k, int delta){
    double top = pow(delta, k) * expf(-delta); // the second expression give me a double 
    long bottom = factorial(k);
    return top/bottom;
}
