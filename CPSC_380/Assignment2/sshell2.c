#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */

int main(void) {
    char input_buffer[MAX_LINE];   // Buffer to store user input
    char *args[MAX_LINE / 2 + 1]; // Array to store command and arguments
    int should_run = 1;           // Flag to determine when to exit the shell

    while (should_run) {
        printf("osh> ");
        fflush(stdout);

        // Read user input
        fgets(input_buffer, sizeof(input_buffer), stdin);

        // Tokenize user input into separate arguments
        char *token = strtok(input_buffer, " \t\n");
        int arg_count = 0;

        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " \t\n");
        }

        // Check for "exit" command to terminate the shell
        if (arg_count > 0 && strcmp(args[0], "exit") == 0) {
            should_run = 0;
            continue;
        }

        // Check for background execution ("&")
        int background = 0;
        if (arg_count > 0 && strcmp(args[arg_count - 1], "&") == 0) {
            background = 1;
            args[arg_count - 1] = NULL; // Remove the "&" from the arguments
        }

        // Fork a child process
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            // In the child process
            // Execute the command using execvp()

            if (execvp(args[0], args) == -1) {
                perror("Exec failed");
                exit(1);
            }
        } else {
            // In the parent process
            // If not background execution, wait for the child
            if (!background) {
                int status;
                waitpid(pid, &status, 0);

                if (WIFEXITED(status)) {
                    // Child process has exited
                    int exit_status = WEXITSTATUS(status);
                    printf("Child process exited with status: %d\n", exit_status);
                }
            }
        }
    }

    printf("Exiting the shell...\n");

    return 0;
}
