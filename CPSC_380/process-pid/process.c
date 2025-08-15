#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    /* for a child process*/
    pid = fork();

    if (pid < 0) { /* Error Occurred*/
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) { /* Child Process*/
        printf("Child Process: ");
        int pid_c = getpid();
        printf("pid is: %d\n", pid_c);
    }
    else { /* Parent Process*/
        wait(NULL);
        printf("Parent Process: ");
        int pid_p = getpid();
        printf("pid is: %d\n", pid_p);
    }

    return 0;
}
