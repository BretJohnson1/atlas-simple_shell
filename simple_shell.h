#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0
#define PATH_MAX 4096

/**
*struct _simpleShell - information representing current state of shell
*@line_num: cuurent line number of script
*@exit_status: EXIT_SUCCESS (0) or EXIT_FAILURE (!)
*@is_active: TRUE (1) or FALSE (0) -- if REPL loop still open
*@path_variable: path variable inherited from environment as string array
*@environment: the environmental variables
*@builtin: function pointer to a builtin command (if any)
*@os_command_path: path to executable file to invoke (if any)
*@command_args: arguments parsed from last line of input
*
*Description: Parameters defining the core interpreter
*/
typedef struct _SimpleShell
{
    int line_num;
    int exit_status;
    int is_active;
    char **path_variable;
    char **environment;
    void (*builtin)(struct _SimpleShell *);
    char *os_command_path;
    char **command_args;
}SimpleShell_t;