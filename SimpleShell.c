#include "simple_shell.h"
/**
*create_shell - allocate memory for the simple shell and set values
*@shell: double pointer back to the simple shell
*@envp: environmental variables passed directly from main
*
*Return: whether or not the shell was successfully created
*/
void create_shell(SimpleShell_t **shell, char **envp)
{
    *shell = malloc(sizeof(SimpleShell_t));
    if (shell == NULL)
    return;

    ((*shell)->line_num) = 0;
    ((*shell)->exit_status) = 0;
    ((*shell)->is_active) = TRUE;
    (*shell)->environment = envp;
    (*shell)->path_variable = split_string(getenv("PATH"), ":");
    (*shell)->os_command_path = NULL;
    (*shell)->builtin = NULL;
}