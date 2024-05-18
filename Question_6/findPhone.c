
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Something ain't right
void Erry(char *progName) {
    fprintf(stderr, "Err: %s \"Name\"\n", progName);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    // Verify command-line arguments
    //you can enter first name, if you want you can also add last name but it doesn't use it to parse
    if (argc != 2 && argc != 3) {
        Erry(argv[0]);
    }

    // Create pipes for inter-process communication
    int inputPipe[2], filterPipe[2], transformPipe[2];

    // Setup the first pipe
    if (pipe(inputPipe) == -1) {
        perror("Failed to create inputPipe");
        exit(EXIT_FAILURE);
    }

    // Create the first child process to read the phonebook
    if (fork() == 0) {
        // Redirect stdout to inputPipe's write-end
        close(inputPipe[0]); // Close unused read-end
        dup2(inputPipe[1], STDOUT_FILENO);
        close(inputPipe[1]); // Close the write-end after duplication

        // Execute 'cat' to read the phonebook
        execlp("cat", "cat", "phonebook.txt", NULL);
        perror("Execution of 'cat' failed");
        exit(EXIT_FAILURE);
    }
    close(inputPipe[1]); // Close write-end in parent process

    // Setup the second pipe
    if (pipe(filterPipe) == -1) {
        perror("Failed to create filterPipe");
        exit(EXIT_FAILURE);
    }

    // Create the second child process to filter entries by name
    if (fork() == 0) {
        // Redirect stdin to inputPipe's read-end and stdout to filterPipe's write-end
        close(filterPipe[0]); // Close unused read-end
        dup2(inputPipe[0], STDIN_FILENO);
        close(inputPipe[0]); // Close the read-end after duplication
        dup2(filterPipe[1], STDOUT_FILENO);
        close(filterPipe[1]); // Close the write-end after duplication

        // Execute 'grep' to filter entries
        execlp("grep", "grep", argv[1], NULL);
        perror("Execution of 'grep' failed");
        exit(EXIT_FAILURE);
    }
    close(inputPipe[0]); // Close read-end in parent process
    close(filterPipe[1]); // Close write-end in parent process

    // Setup the third pipe
    if (pipe(transformPipe) == -1) {
        perror("Failed to create transformPipe");
        exit(EXIT_FAILURE);
    }

    // Create the third child process to replace commas with spaces
    if (fork() == 0) {
        // Redirect stdin to filterPipe's read-end and stdout to transformPipe's write-end
        close(transformPipe[0]); // Close unused read-end
        dup2(filterPipe[0], STDIN_FILENO);
        close(filterPipe[0]); // Close the read-end after duplication
        dup2(transformPipe[1], STDOUT_FILENO);
        close(transformPipe[1]); // Close the write-end after duplication

        // Execute 'sed' to replace commas with spaces
        execlp("sed", "sed", "s/,/ /g", NULL);
        perror("Execution of 'sed' failed");
        exit(EXIT_FAILURE);
    }
    close(filterPipe[0]); // Close read-end in parent process
    close(transformPipe[1]); // Close write-end in parent process

    // Create the fourth child process to extract the phone number
    if (fork() == 0) {
        // Redirect stdin to transformPipe's read-end
        dup2(transformPipe[0], STDIN_FILENO);
        close(transformPipe[0]); // Close the read-end after duplication

        // Execute 'awk' to print the third field
        execlp("awk", "awk", "{print $3}", NULL);
        perror("Execution of 'awk' failed");
        exit(EXIT_FAILURE);
    }
    close(transformPipe[0]); // Close read-end in parent process

    // Wait for all child processes to complete
    while (wait(NULL) > 0);

    return 0;
}
