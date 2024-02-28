#ifndef MAIN_H
#define MAIN_H
extern char **environ;

#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void reverse_str(char *str);
char *int_to_str(int n, char *str);
char **divide(char *line, int *argc);
int execute(char **argv, int compt);
char *find_path(char *str);
#endif
