#include "simple_shell.h"

/**
* main - entry pointer for program
*@argc: number of arguments passed to program
*@argv: what arguments there were, if any
*@envp: complete list of environmental variables
*
*Return: EXIT_SUCCESS (0) or EXIT_FAILURE (1)
*/
int main(
	__attribute__((unused)) int argc,

	__attribute__((unused)) char *argv[],

	char **envp)
{
SimpleShell_t *shell = NULL;
int exit_status = 0;

/**check if the shell is running interactively*/
int is_interactive = isatty(STDIN_FILENO);

/**create a new shell instance and initialize it with environment variables*/
create_shell(&shell, envp);
/**if shell is running interactively, launch REPL*/
if (is_interactive)
	launch_repl(shell);
/**if shell is not interactive, read and execute from a script*/
else
	read_script(shell);
/**free memory allocated for the shell*/
free_shell(shell);
/**return the exit status of the shell*/
return (exit_status);
}

/**
*launch_repl - open a R.E.P.L. with interpreter
*@shell: double pointer back to the interpreter
*
*Return: void (for now)
*/
void launch_repl(SimpleShell_t *shell)
{
char *line = NULL;

/**loop until shell is active*/
while (shell->is_active == TRUE)
{
	printf("(OMG what now!?) ");
	line = take_input();
	parse_line(shell, line);
	free(line);
	fflush(NULL);
}
}

/**
*read_script - read a script as piped in from stdin
*@shell: double pointer back to the interpreter
*
*Return: void
*/
void read_script(SimpleShell_t *shell)
{
char *current_line = NULL;

/**loop until the shell is active*/
do {
	/**read a line from the script*/
	current_line = take_input();
	/**if a line was successfully read, parse and execute the command*/
	if (current_line != NULL)
	parse_line(shell, current_line);
	/**if reading a line failed, set the sehll to inactive*/
	else
	(shell->is_active) = FALSE;
	/**free memory allocated for the current line*/
	free(current_line);
	/**flush output buffers to ensure immediate display of prompts/messeges*/
	fflush(NULL);

}
/**continue looping while the shell is active*/
while
(shell->is_active == TRUE);
}
