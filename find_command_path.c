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

  command_path = malloc(sizeof(char) * 255)

  snprintf(command_path, 255, "%s", shell->command_args[0]);

  while(shell->path_variable[i])
  {
    if (stat(command_path, &file_info) == 0)
    return (command_path);

    test_path = create_test_path(
      shell->path_variable[i++],
      shell->command_args[0]
    );
    snprintf(command_path, 255, "%s", test_path);
    free(test_path);
  }
  free(command_path);
  return (NULL);
  }