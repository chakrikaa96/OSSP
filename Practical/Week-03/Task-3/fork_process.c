#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void display_process_info(const char *process, const char *state)
{
    printf("%s Process\n", process);
    printf("PID  : %d\n", getpid());
    printf("PPID : %d\n", getppid());
    printf("State: %s\n\n", state);
}

int main()
{
    pid_t pid;

    printf("Before fork()\n");
    printf("Parent PID: %d\n\n", getpid());

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    else if (pid == 0)
    {
        /* Child Process */
        display_process_info("Child", "Running");

        printf("Child is sleeping for 5 seconds...\n");
        printf("Child PID: %d\n\n", getpid());

        sleep(5);

        printf("Child Process\n");
        printf("PID  : %d\n", getpid());
        printf("PPID : %d\n", getppid());
        printf("State: Exiting\n\n");

        printf("Child exiting...\n");
        exit(0);
    }

    else
    {
        /* Parent Process */
        display_process_info("Parent", "Running");

        printf("Created Child PID: %d\n\n", pid);

        printf("Parent is waiting for the child...\n");
        printf("Parent State: Waiting\n\n");

        wait(NULL);

        printf("Child terminated.\n");
        printf("Parent PID : %d\n", getpid());
        printf("Parent PPID: %d\n", getppid());
        printf("Parent State: Running\n\n");

        printf("Parent exiting...\n");
    }

    return 0;
}
