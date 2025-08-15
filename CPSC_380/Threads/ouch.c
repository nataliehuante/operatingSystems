#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig) {
    printf("OUCH! = I got signal %d\n", sig);
    (void) signal(SIGINT, SIG_DFL); // redefines it back to the original function
}

int main() {
    (void) signal(SIGINT, ouch); // overrides the system call SIGINT

    while(1) {
        printf("Hello World\n");
        sleep(1)
;    }
}