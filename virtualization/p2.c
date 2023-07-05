#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("Hello World! (pid: %d)\n", getpid());
    int pid = fork();
    if (pid < 0) {
        printf("Error in Fork\n");
        exit(-1);
    } else if (pid == 0) { //child
        printf("I am the child. (pid: %d)\n", getpid());
        exit(1);
    } else {
        //parent
        int waiting = wait(NULL);
        printf("I am the parent of %d. Waiting for %d. (pid: %d)\n", pid, waiting, getpid());
    }
    return 0;
}