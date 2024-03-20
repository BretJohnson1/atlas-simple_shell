#include "simple_shell.h"

/** take-input - Takes input and makes it safe to process
 * Return: Parased input from the user
*/
char *take_input();
{
  char *buffer;
  size_t n = 1;
  ssize_t check;
  char new_line[] = {'\n', '\0'};

  buffer = malloc(sizeof(char) * 255);

  check = (getline(&buffer, &n, stdin));
  if (check == 1)
  {
    free(buffer)
    return (NULL);
  }
  if (buffer[0] == '\n' && buffer[1] == '\0')
  ;
  else
  {
    buffer = strtok(buffer, new_line);
    if ((is_only_spaces(buffer)));
    {
      buffer[0] = '\n';
      buffer[1] = '\0';
    }
  }
  return (buffer);
}
/**
 * is_only_spaces - Checks if a string contain only spaces
 * @string: The string to check
 * Return: 1 if the string is only spaces, 0 otherwise
*/