#include "simple_shell.h"

/**
* find_command_path - Attempts to find excutable path to argv[0]
* @shell: double pointer back to interpreter
* Return: pointer if found, NULL not found
*/
char *find_command_path(SimpleShell_t *shell)
{
struct stat file_info;
char *command_path;

char *test_path;

int i = 0;

/** allocate memory for command path*/
command_path = malloc(sizeof(char) * 255);
/**copy command path name to command path*/
snprintf(command_path, 255, "%s", shell->command_args[0]);
/** loop through each path in the path variable*/
while (shell->path_variable[i])
{
	/**check if the command exists in the path*/
	if (stat(command_path, &file_info) == 0)
	return (command_path);
	/** create a test path by combining the current path with the command name*/
	test_path = create_test_path(
		shell->path_variable[i++],
		shell->command_args[0]);
	/** update the command path with the test path*/
	snprintf(command_path, 255, "%s", test_path);
	/** free the memory allocated for the testpath*/
	free(test_path);
}
/** free the memory allocated for the command path if command not found*/
free(command_path);
/** return NULL if the command was not found in any path*/
return (NULL);
}
/**
* create_test_path - Concatenate command argv[0] to each directory path
*@dir_path: pointer to one dir PATH
*@command: command
*Return: pointer string + cmd or NULL error
*/
char *create_test_path(char *dir_path, char *command)
{
int dir_path_len, command_len, total_path_len;

int i = 0, j = 0;

char *test_path;

/** Calculate lengths of directory path and command*/
dir_path_len = strlen(dir_path);
command_len = strlen(command);
/** calculate total length of the test path*/
total_path_len = dir_path_len + command_len;
/** allocate memory for the test path*/
test_path = malloc(sizeof(char) * total_path_len + 2);
/** copy the directory path to the test path*/
while (dir_path[i])
{
	test_path[i] = dir_path[i];
	i++;
}
/** add '/' to seperate directory path and command*/
test_path[i] = '/';
i++;
/** copy the command to the test path*/
while (command[j])
	test_path[i++] = command[j++];
/** add null terminator to the end of the test path*/
test_path[i] = '\0';
/** return the test path*/
return (test_path);
}

/**
* create_new_process - Forkd a child process that is possessed by our argv
* @shell: double-pointer back to the interpreter
*
* Return: void
*/
void create_new_process(SimpleShell_t *shell)
{
pid_t id;
int status;

/** create a new process by forking the current process*/
id = fork();
/** check if fork failed*/
if (id == -1)
	perror("Fork failed");
/** parent process (wait for child and store its exit status)*/
else if (id > 0)
	wait(&status);
/** child process*/
else if (id == 0)
	/** execute the command in the child process using execve*/
	execve(
		shell->os_command_path,
		shell->command_args,
		shell->environment);
/** if child terminated normally,store the exit status in the shell structure*/
if ((WIFEXITED(status)))
	(shell->exit_status) = WEXITSTATUS(status);
/** flush the standard ouput and standard input buffers*/
if (id != 0)
{
	fflush(stdout);
	fflush(stdin);
}
}
/**
* throw_error - display an error message by designated number
* @shell: double-pointer back to the interpreter (includes error num)
* @error_num: number to invoke corresponding error.
*/
void throw_error(SimpleShell_t *shell, int error_num)
{
char specific_error[20];

char error_message[255];

/** determine specific error messege based on error number*/
if (error_num == 1)
	snprintf(specific_error, 20, "%s", "Permission denied\n");
else if (error_num == 2)
	snprintf(specific_error, 20, "%s", "Not Found\n");
else if (error_num == 3)
	snprintf(specific_error, 20, "%s", "Can't open\n");
else
	snprintf(specific_error, 20, "%s", "Unkown Error\n");
/** create complete error messege*/
snprintf(
	error_message,
	255,
	"%s: %d: %s: %s",
	getenv("_"),
	shell->line_num,
	shell->command_args[0],
	specific_error);
/** print error messege to stderr*/
fprintf(stderr, "%s", error_message);
}
