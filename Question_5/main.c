#include "header.h"

void Erry(const char *prog_name) {
    fprintf(stderr, "Error: %s \"seed\" \"size\"\n", prog_name); //what you should do
    exit(EXIT_FAILURE);
}
int main(int argc, char *argv[]){
    if (argc != 3){
        Erry(argv[0]); // man what do you think you're doing
    }
    int seed = atoi(argv[1]);
    int size = atoi(argv[2]);
    maxsubarray(seed, size);
    return 0;
}