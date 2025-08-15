#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command*/

int main(void) {

    char *args[MAX_LINE/2 + 1]; // command line arguments
    int should_run = 1; // flag to determine when to exit program

    while (should_run) {
        fflush(stdout); // flushes out any output 
        printf("osh>"); // prompt the user for input 
        
        char input_string[MAX_LINE]; // input buffer
        
        
        // (1) READ USER INPUT
        if ( fgets(input_string, sizeof(input_string), stdin) != NULL ) {
    
            size_t length = strlen(input_string); // length of the input
            
            // get rid of any trailing newline character
            if (length > 0 && input_string[length - 1] == '\n') {
                input_string[length - 1] = '\0';
            }

            // initialize args to NULL in case there is old input string
            for (int i = 0; i < sizeof(args) / sizeof(args[0]); i++) {
                args[i] = NULL;
            }

            // (2) PARSE INPUT STRING INTO ARGS 
            char *current_word;
            int args_index = 0;

            // strtok() gets the first word before hitting a space and returns it
            current_word = strtok(input_string, " ");

            while (current_word != NULL) {
                // if the word is "exit", exit the while loop *don't even store it in args*
                if (strcmp(current_word, "exit") == 0 || strcmp(current_word, "Exit") == 0) {
                    should_run = 0;
                    break;
                }
                // if there is a word present that is not "exit" or "Exit", add it to args 
                args[args_index] = current_word;
                
                // increase index
                args_index++;

                // get the next token *NULL as first param indicates to pick up where the last strtok() call left off*
                current_word = strtok(NULL, " ");
            }

            // (3) CHECK FOR "&" ARGUMENT
            int wait = 1; // indicates if the parent should wait for the child

            if ((args_index > 0) && (strcmp(args[args_index - 1], "&") == 0)) {
                wait = 0;
                // remove "&" from args so it is not passed in as a parameter to child process
                args[args_index - 1] = NULL;
            }


            /* (4) FORK A CHILD PROCESS*/
            pid_t child_pid;
            child_pid = fork();
            
            if (child_pid < 0) { // Error Occurred
                fprintf(stderr, "Fork Failed");
                return 1;
            }
            else if (child_pid == 0) { // Child Process
                // the child will execute the execvp() function
                execvp(args[0], args);
            }
            else { // Parent Process
                int status;
                // unless specified by a "&", the parent will wait
                if (wait) {
                    waitpid(child_pid, &status, 0);

                    /* we do not need the exit status, but waiting for it will allow the child to output the command's 
                    output before the parent continues to the next osh> prompt */
                    if (WIFEXITED(status)) {
                        // child process has exited
                        int exit_status = WEXITSTATUS(status);
                    }
                }
            }
        }
        else { // if the line read is in fact NULL
            printf("There was an error reading your input.\n");
        }
    }

    // user has exited the loop
    printf("Exiting...\n");

    return 0;
}