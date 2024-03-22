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


}