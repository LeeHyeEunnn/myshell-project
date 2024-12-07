#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_external_command(char *argv[]) {
    pid_t pid = fork(); // Create a new process

    if (pid == 0) { // Child process
        if (execvp(argv[0], argv) == -1) { // Execute the external command
            perror("Error executing command");
        }
        exit(EXIT_FAILURE); // Exit child process if execvp fails
    } else if (pid > 0) { // Parent process
        wait(NULL); // Wait for the child process to finish
    } else { // Fork failed
        perror("Fork failed");
    }
}
