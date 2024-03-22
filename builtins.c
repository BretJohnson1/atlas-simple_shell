#include "simple_shell.h"
/**
*quit_repl - quit interactive mode
*@shell: double pointer back to shell interpreter
*Description: placeholder
*/
void quit_repl(SimpleShell_t *shell)
{
    (shell->is_active) = FALSE;
}

/**
*print_env_variables - print list of environmental vaiables
*@shell: double pointer back to shell interpreter
*Description: placeholder
*/
void print_env_variables(SimpleShell_t *shell)
{
    int i = 0;

    do {
        printf("%s\n", shell->environment[i++]);
    } while (shell->environment[i]);
}