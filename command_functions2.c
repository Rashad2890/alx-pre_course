#include "main.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

char **get_command(void)
{
    char **command = NULL;
    char *fcommand = NULL;
    size_t size = 1024;
    int i = 0;

    getline(&fcommand, &size, stdin);
    fcommand[strlen(fcommand) - 1] = '\0';
    command = malloc(sizeof(char *));
    if (!command)
        return NULL;
    command[0] = strtok(fcommand, " ");
    for (i = 1; ; i++)
    {
        command = realloc(command, (i + 1) * sizeof(char *));
        if (!command)
            return NULL;
        command[i] = strtok(NULL, " ");
        if (!command[i])
            break;
    }
    return command;
}

char *which(const char *command)
{
    char *path = getenv("PATH");
    char *full_path = NULL;
    char *token;
    char *delim = ":";

    if (!path)
        return NULL;

    token = strtok(path, delim);
    while (token)
    {
        full_path = malloc(strlen(token) + strlen(command) + 2);
        if (!full_path)
            return NULL;

        sprintf(full_path, "%s/%s", token, command);
        if (access(full_path, X_OK) == 0)
            return full_path;

        free(full_path);
        token = strtok(NULL, delim);
    }

    return NULL;
}
