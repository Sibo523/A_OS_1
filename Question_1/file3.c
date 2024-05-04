#include <stdio.h>
#include <stdlib.h>
void main(){
    //accessing undifined memory location
    int *ptr = 7;
    printf("%d", *ptr);
    return;
}