#ifndef FUNCTIONS
#define FUNCTIONS

extern char **get_command(void);
extern int setenv(const char *name, const char *value, int overwrite);
char *which(const char *command);

#endif /*FUNCTIONS*/
