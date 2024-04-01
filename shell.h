#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

void tokenize_string(char *str, char *delims, char **tokens);
int make_a_baby(char *stdpath, char *call_path, char **str_arr);
int check_path(char *stdpath, char **path_array, char **token_array);

char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
int _strncmp(char *s1, char *s2, int n);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);

#endif
