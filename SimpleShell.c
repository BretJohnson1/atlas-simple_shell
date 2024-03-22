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

/**
*parse_line - parses an individual line taken from a script or the REPL
*@shell: double pointer back to the simple shell
*@new_line: the new line to be parsed
*
*Description: will require significant overhaul to support pipes
*/
void parse_line(SimpleShell_t *shell, char *new_line)
{
    shell->command_args = split_string(new_line, " ");

    shell->builtin = get_builtin(shell->command_args[0]);

    shell->os_command_path = find_command_path(shell);

    if (shell->builtin != NULL)
    shell->builtin(shell);
    else if (shell->os_command_path != NULL)
    create_new_process(shell);
    else
    throw_error(shell, 2);

    free_array(shell->command_args);
    free(shell->os_command_path);
}