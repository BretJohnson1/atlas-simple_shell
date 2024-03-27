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
{
do
	/**print the current envrionment variable to the standard output*/
	printf("%s\n", shell->environment[i++]);
	/**continue looping until a NULL pointer is reached*/
} while (shell->environment[i]);
}
