#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * which - finds the full path of a command in the PATH environment variable
 * @command: the command to search for
 *
 * Return: a pointer to the full path of the command, or NULL if not found
 */
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
