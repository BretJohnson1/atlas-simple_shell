#include "simple_shell.h"

/**
*create_shell - allocate memory for the simple shell and set values
*@shell: double pointer back to the simple shell
*@envp: environmental variables passed directly from main
*
*Return: whether or not the shell was successfully creatd
*/
void create_shell(SimpleShell_t **shell, char **envp)
{
*shell = malloc(sizeof(SimpleShell_t));
/**check if allocation was successful*/
if (shell == NULL)
	return;
/**initializing various members of the structure*/
/**set line number to 0*/
((*shell)->line_num) = 0;
/**set exit status to 0*/
((*shell)->exit_status) = 0;
/**set the shell as active*/
((*shell)->is_active) = TRUE;
/**copy envrionment variables into the shell*/
(*shell)->environment = envp;
/**split path variables into an array of directories and assign it to path_variable*/
(*shell)->path_variable = split_string(getenv("PATH"), ":");
/**set the os_command_path to NULL initially*/
(*shell)->os_command_path = NULL;
/**set the builtin command to NULL initially*/
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
/**split the input line into individual command arguments*/
shell->command_args = split_string(new_line, " ");
/**determine if the command is a builtin command and assign the correspeonding function pointer*/
shell->builtin = get_builtin(shell->command_args[0]);
/**find the path of the os command executable*/
shell->os_command_path = find_command_path(shell);
/**check if the command is a built in command*/
if (shell->builtin != NULL)
	/**if it is a built in command, execute it*/
	shell->builtin(shell);
/**if the command is not a built in but the os command path is found, create a new process to execute it*/
else if (shell->os_command_path != NULL)
	create_new_process(shell);
/**if it is niether a built in or os, then throw error "not found"*/
else
	throw_error(shell, 2);

free_array(shell->command_args);
free(shell->os_command_path);
}
/**
*free_shell - deallocates memory for the interpreter and its priorities
*@shell: double pointer back to the simple shell
*/
void free_shell(SimpleShell_t *shell)
{
free_array(shell->path_variable);

free(shell);
}

/**
*free_array - deallocates memory allocated through split_string function
*@an_array: the array that needs to be deallocated
*/
void free_array(char **an_array)
{
int i;

for (i = 0; an_array[i]; i++)
	free(an_array[i]);

free(an_array);
}

/**
*get_builtin - runs through and tries to find built in commands
*@command: the command we're looking for as a string
*
*Return: function pointer back to command to execute
*/
void (*get_builtin(char *command))(SimpleShell_t *)
{
int i;

/**defining an array of structures representing builtin commands*/
BuiltInCommand_t builtins[] = {
	{"exit", quit_repl},
	{"quit", quit_repl},
	{"env", print_env_variables},
	{NULL, NULL}};
/**loop through the array of builtin commands*/
for (i = 0; builtins[i].name; i++)
{
	/**check if the current command matches any builtin command*/
	if (strcmp(command, builtins[i].name) == 0)
	/**if a match is found, return the corresponding function pointer*/
	return (builtins[i].exec);
}
/**if no match is found, return NULL*/
return (NULL);
}
