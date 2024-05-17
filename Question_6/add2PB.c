#include <stdio.h>
#include <stdlib.h>

void Erry(const char *prog_name) {
    fprintf(stderr, "Error: %s \"Name\" \"last name\" \"Phone Number\"\n", prog_name); //what you should do
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 4) { // (first name) (last name), phone number
        Erry(argv[0]);
    }

    FILE *file = fopen("phonebook.txt", "a"); // we want to append a new person to the phonebook
    
    if (!file) { // check if we managed to open
        perror("fopen didn't work");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s %s,%s \n", argv[1], argv[2],argv[3]); // write the new person to the phonebook
    fclose(file); 

    return 0;
}
