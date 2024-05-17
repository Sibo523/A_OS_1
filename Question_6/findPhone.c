#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void erry(const char *prog_name) {
    fprintf(stderr, "Erry: %s \"Name\"\n", prog_name); // what you should do
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
   if (argc > 3 || argc == 1) { 
       erry(argv[0]);
    }

    int pipe1[2];
    int pipe2[2];
    int pipe3[2];
    
    if (pipe(pipe1) == -1) {
        perror("pipe1");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) { //god is good 
        // First child process: `cat phonebook.txt`
        close(pipe1[0]);
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[1]);
        execlp("cat", "cat", "phonebook.txt", (char *)NULL);
        perror("execlp cat");
        exit(EXIT_FAILURE);
    }

    close(pipe1[1]);

    if (pipe(pipe2) == -1) {
        perror("pipe2");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) {
        // Second child process: `grep "Name"`
        close(pipe2[0]);
        dup2(pipe1[0], STDIN_FILENO);
        close(pipe1[0]);
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe2[1]);
        execlp("grep", "grep", argv[1], (char *)NULL);
        perror("execlp grep");
        exit(EXIT_FAILURE);
    }

    close(pipe1[0]);
    close(pipe2[1]);

    if (pipe(pipe3) == -1) {
        perror("pipe3");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) {
        // Third child process: `sed 's/,/ /'`
        close(pipe3[0]);
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[0]);
        dup2(pipe3[1], STDOUT_FILENO);
        close(pipe3[1]);
        execlp("sed", "sed", "s/,/ /", (char *)NULL);
        perror("execlp sed");
        exit(EXIT_FAILURE);
    }

    close(pipe2[0]);
    close(pipe3[1]);

    if (fork() == 0) {
        // Fourth child process: `awk '{print $2}'`
        dup2(pipe3[0], STDIN_FILENO);
        close(pipe3[0]);
        execlp("awk", "awk", "{print $3}", (char *)NULL);
        perror("execlp awk");
        exit(EXIT_FAILURE);
    }

    close(pipe3[0]);

    // Wait for all child processes to finish
    while (wait(NULL) > 0);

    return 0;
}
