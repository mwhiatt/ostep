#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pid = fork();
    if (pid < 0) {
        printf("Error in Fork\n");
        exit(-1);
    } else if (pid == 0) { //child
        printf("I am a child. (pid: %d).\n", getpid());
        close(STDOUT_FILENO);
        open("p4out.txt", O_CREAT | O_WRONLY | O_TRUNC, 777);
        char *args[3];
        args[0] = strdup("wc");
        args[1] = strdup("p4.c");
        args[2] = NULL;
        execvp(args[0], args);
    } else {
        //parent
        int waiting = wait(NULL);
        printf("Done waiting for %d.\n", waiting);
    }
    return 0;
}