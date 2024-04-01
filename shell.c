#include "shell.h"

void no_more_betty(void);

/**
 * main - Entry point for ghost
 * @argc: arg count
 * @argv: array of input arg strings
 * @env: array of env strings
 * Return: Always 0. Exit status differs.
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL, *path = NULL;
	size_t nread = 0;
	char *args[20], *paths[20];
	int ret_val = 0;
	int i;
/** ignore used arguments*/
	(void) argc;
	(void) argv;
/** main shell loop*/
	while (1)
	{
		i = 0;
/** extract PATH environment variable*/
		while (env[i])
		{
			if (_strncmp(env[i], "PATH=", 5) == 0)
			{
				path = _strdup((env[i] + 5));
				break;
			}
			i++;
		}
/** tokenize the PATH variable*/
		tokenize_string(path, ":", paths);
/** print shell prompt if running interactively*/
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$uh Dude: ", 11);
/** read input line*/
		if (getline(&line, &nread, stdin) == -1)
		{
			free(line);
			free(path);
			exit(EXIT_SUCCESS);
		}
/** tokenize input line*/
		tokenize_string(line, " \n\t", args);
/** handle built in commands or execute external commands*/
		if (!args[0])
		{
			free(path);
			continue;
		}
		if (_strcmp(args[0], "exit") == 0)
		{
			free(line);
			free(path);
			exit(EXIT_SUCCESS);
		}
		if (_strcmp(args[0], "env") == 0)
		{
			for (i = 0 ; env[i] != NULL ; i++)
			{
				write(STDOUT_FILENO, env[i], _strlen(env[i]));
				write(STDOUT_FILENO, "\n", 1);
			}
			free(path);
			continue;
		}
/** check if command is executbale*/
		if (access(args[0], X_OK) == 0)
			make_a_baby(path, args[0], args);
		else
			ret_val = check_path(path, paths, args);

	}
	return (ret_val);
}
/**
 * tokenize_string - tokenize a string
 * @line: string to tokenize
 * @delims: delimiter string
 * @tokens: array to save tokens
 * Return: void
 */
void tokenize_string(char *line, char *delims, char **tokens)
{
/** use strtok to tokenize the input line based on delimiters*/
	char *path_token = strtok(line, delims);
	int i = 0;
/** iterate through the tokens and store them in the tokens array*/
	while (path_token != NULL)
	{
		tokens[i] = path_token;
		i++;
		path_token = strtok(NULL, delims);
	}
/** set the last element of the tokens array to NULL to mark the end*/
	tokens[i] = NULL;
}
/**
* check_path - checks if command is in path
* @path: path string
* @patharr: array of path strings
* @args: array of input arg strings
* Return: 0 on success, 1 on failure
*/
int check_path(char *path, char **patharr, char **args)
{
	int i = 0;
	char *comp_path = NULL;
	struct stat x;
/** loop through each path in the patharr array*/
	while (patharr[i] != NULL)
	{
/** allocate memory for the complate path*/
		comp_path = malloc(_strlen(args[0]) + _strlen(patharr[i]) + 2);
/** copy the directory path from patharr[i] to comp_path*/
		_strcpy(comp_path, patharr[i]);
/** concatenate '/' to the directory path*/
		_strcat(comp_path, "/");
/** concatenate the command name to the complete path*/
		_strcat(comp_path, args[0]);
/** check if the complete path exists and is exectuable*/
		if (stat(comp_path, &x) == 0)
		{
/** if the file exists and is exectuable, execute it*/
			make_a_baby(path, comp_path, args);
			free(comp_path);
			return (0);
		}
/** free memory allocated for comp_path*/
		free(comp_path);
		i++;
	}
/** if no executable is found, return 127*/
	return (127);
}


/**
 * make_a_baby - creates a child process
 * @stdpath: path string
 * @call_path: path to executable
 * @str_arr: array of tokens
 * Return: status of child process
 */

int make_a_baby(char *stdpath, char *call_path, char **str_arr)
{
	pid_t cop;
	pid_t sig;
	int status = 0;
/** free memory allocated for stdpath*/
	free(stdpath);
/** fork a new process*/
	cop = fork();
	if (cop == 0)
	{
/** execute the command with the given path and arguments*/
		if (execve(call_path, str_arr, NULL) == -1)
/** exit child process if execution fails*/
			exit(EXIT_FAILURE);
	}
	else if (cop < 0)
	{
/** fork failed, exit with failure status*/
		exit(EXIT_FAILURE);
	}
	else
	{
		do {
/** wait for the child process to terminate or stop*/
			sig = waitpid(cop, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
/** return the status of the child process to the caller*/
	(void) sig;
	return (status);
}
/**
 * *_strdup - ret ptr to newly allocated mem space
 * @str: string
 * Return: NULL or ptr to dupe string
 */
char *_strdup(char *str)
{
	int i = 0;
	int n = 0;
	char *ar;
/** check if the input string is NULL*/
	if (str == NULL)
	{
		return (NULL);
	}
/** calculate the length of the input string*/
	while (str[i] != '\0')
	{
		i++;
		n++;
	}
/** increment n to account for the NULL terminator*/
	n++;
/** allocate memory for the duplicate string*/
	ar = malloc(n * sizeof(char));
	if (ar == NULL)
	{
		return (NULL);
	}
/** copy the contents of the input string to the duplicate string*/
	for (i = 0 ; i < n ; i++)
	{
		ar[i] = str[i];
	}
/** return the pointer to the duplicate string*/
	return (ar);
}
