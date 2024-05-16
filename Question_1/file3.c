#include <stdio.h>
#include <stdlib.h>
void main(){
    //accessing undifined memory location
    int *ptr = NULL;
    *ptr = 7;
    printf("%d", *ptr); // won't get executed
    return;
}