#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Something ain't right
void Erry(char *progName) {
    fprintf(stderr, "Err: %s \"Name\" [\"Additional Name\"]\n", progName); //bruv
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    // Verify command-line arguments should have 2 or 3 arguments
    if (argc != 2 && argc != 3) {
        Erry(argv[0]);
    }

    // Create pipes for inter-process communication
    int inputPipe[2], filterPipe[2], intermediatePipe[2], transformPipe[2];

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

    // Create the second child process to filter entries by the first name
    if (fork() == 0) { // the first filter 

        // Redirect stdin to inputPipe's read-end and stdout to filterPipe's write-end
        close(filterPipe[0]);
        dup2(inputPipe[0], STDIN_FILENO);
        close(inputPipe[0]); 
        dup2(filterPipe[1], STDOUT_FILENO);
        close(filterPipe[1]); 

        // Execute 'grep' to filter entries
        execlp("grep", "grep", argv[1], NULL); // apply the first filter (first name)
        perror("Execution of 'grep' failed");
        exit(EXIT_FAILURE);
    }
    close(inputPipe[0]); 
    close(filterPipe[1]); 

    if (argc == 3) { // apply the second filter
        // Setup an intermediate pipe
        if (pipe(intermediatePipe) == -1) {
            perror("Failed to create intermediatePipe");
            exit(EXIT_FAILURE);
        }

        // Create the third child process to filter entries by the second name
        if (fork() == 0) {
            // Redirect stdin to filterPipe's read-end and stdout to intermediatePipe's write-end
            close(intermediatePipe[0]);
            dup2(filterPipe[0], STDIN_FILENO);
            close(filterPipe[0]); 
            dup2(intermediatePipe[1], STDOUT_FILENO);
            close(intermediatePipe[1]); 

            // Execute 'grep' to filter entries
            execlp("grep", "grep", argv[2], NULL); // appply the second filter (last name)
            perror("Execution of 'grep' failed");
            exit(EXIT_FAILURE);
        }
        close(filterPipe[0]); 
        close(intermediatePipe[1]); 
        // Use intermediatePipe for further processing
        filterPipe[0] = intermediatePipe[0]; // get back to filterpipe after applying the second filter (just looks better to me)
    }

    // Setup the third pipe
    if (pipe(transformPipe) == -1) {
        perror("Failed to create transformPipe");
        exit(EXIT_FAILURE);
    }

    // Create the fourth child process to replace commas with spaces
    if (fork() == 0) {
        // Redirect stdin to filterPipe's read-end and stdout to transformPipe's write-end
        close(transformPipe[0]); 
        dup2(filterPipe[0], STDIN_FILENO);
        close(filterPipe[0]); 
        dup2(transformPipe[1], STDOUT_FILENO);
        close(transformPipe[1]); 

        // Execute 'sed' to replace commas with spaces
        execlp("sed", "sed", "s/,/ /g", NULL);
        perror("Execution of 'sed' failed");
        exit(EXIT_FAILURE);
    }
    close(filterPipe[0]); 
    close(transformPipe[1]); 

    // Create the fifth child process to extract the phone number onto the terminal
    if (fork() == 0) {
        // Redirect stdin to transformPipe's read-end
        dup2(transformPipe[0], STDIN_FILENO);
        close(transformPipe[0]); 

        // Execute 'awk' to print the third field
        execlp("awk", "awk", "{print $3}", NULL);
        perror("Execution of 'awk' failed");
        exit(EXIT_FAILURE);
    }
    close(transformPipe[0]); 

    // Wait for all the kids to hang out
    while (wait(NULL) > 0);

    return 0;
}
