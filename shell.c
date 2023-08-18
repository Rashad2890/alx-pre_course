#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

int main(void)
{
    char **command;
    char *full_path; // Declare full_path variable here
    pid_t pid;
    int status;

    while (!feof(stdin))
    {
        printf("#cisfun$ ");
        command = get_command();
        full_path = which(command[0]);
        if (!full_path)
        {
            printf("Could not find command: %s\n", command[0]);
            continue;
        }
        pid = fork();
        if (pid)
            wait(&status);
        else
        {
            if (execve(command[0], command, NULL) < 0)
                printf("No such file or directory\n");
        }
    }
    return (0);
}
