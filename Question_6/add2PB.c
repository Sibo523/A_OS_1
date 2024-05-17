#include <stdio.h>
#include <stdlib.h>

void usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s \"Name\" \"Phone Number\"\n", prog_name);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        usage(argv[0]);
    }

    FILE *file = fopen("phonebook.txt", "a");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s, %s\n", argv[1], argv[2]);
    fclose(file);

    return 0;
}
