
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int factorial (int n){ //classing function factorial rec
    if (n == 0){
        return 1;
    }
    return n*factorial(n-1);
}

void poi(int k, int delta){
    double top = pow(delta, k) * exp(-delta); // the second expression give me a double 
    int bottom = factorial(k);
    printf("%f", top/bottom); //will produce float number, so I need to use %f
}

int main (int argc, char *argv[]){
    if (argc != 3){
        printf("Error: incorrect number of arguments\n");
        return 1;
    }
    int delta = atoi(argv[1]);
    int k = atoi(argv[2]);
    poi(k, delta);
    return 0;
}