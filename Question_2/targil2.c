
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long factorial (int n){ //classing function factorial rec
    if (n == 0){
        return 1;
    }
    return n*factorial(n-1);
}

void poi(int k, int delta){
    double top = pow(delta, k) * expf(-delta); // the second expression give me a double 
    long bottom = factorial(k);
    printf("%lf", top/bottom); //if we want scientific notation we can use %Le
}

int main (int argc, char *argv[]){
    if (argc != 3){
        printf("Error\n");
        return 1;
    }
    int delta = atoi(argv[1]);
    int k = atoi(argv[2]);
    poi(k, delta);
    return 0;
}