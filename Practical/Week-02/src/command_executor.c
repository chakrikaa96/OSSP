#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char input[200];
    char *args[20];
    int count = 0;
    pid_t pid;
    int status;

    printf("Enter a Linux command: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    // Split command into arguments
    char *token = strtok(input, " ");

    while (token != NULL && count < 19) {
        args[count++] = token;
        token = strtok(NULL, " ");
    }

    args[count] = NULL;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("\nChild Process\n");
        printf("Parent PID : %d\n", getppid());
        printf("Child PID  : %d\n", getpid());

        printf("\nExecuting command: %s\n\n", args[0]);

        execvp(args[0], args);

        // Only reached if execvp fails
        perror("exec failed");
        exit(1);
    }
    else {
        // Parent process
        printf("\nParent Process\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        // Wait for child to finish
        wait(&status);

        printf("\nChild process completed.\n");
    }

    return 0;
}
