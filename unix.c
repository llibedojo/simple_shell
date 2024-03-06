#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(void) {
    char buffer[BUFFER_SIZE];

    while (1) {
        // Display prompt
        printf("$ ");

        // Read input from user
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            if (feof(stdin)) {
                printf("\n");
                break;  // Exit if end of file (Ctrl+D) is detected
            } else {
                perror("fgets");
                exit(EXIT_FAILURE);
            }
        }

        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        // Execute command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execlp(buffer, buffer, NULL) == -1) {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        }
    }

    return EXIT_SUCCESS;
}

