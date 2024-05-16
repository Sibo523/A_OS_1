#include "header.h"
//argv [1] = seed, argv[2] = size
int main(int argc, char *argv[]){
    int seed = atoi(argv[1]);
    int size = atoi(argv[2]);
    maxsubarray(seed, size);
    return 0;
}