#include "simple_shell.h"

/**
 * take_input - Takes input and makes it safe to process
* Return: Parased input from the user
*/
char *take_input()
{
/** Storage for our string*/
char *buffer;

/**For keeping count which part of the buffer were at*/
size_t n = 1;
/**Will check if lines only 1 byte*/
ssize_t check;
/**So we can specifically call out '\n' and '\0'*/
char new_line[] = {'\n', '\0'};

/**Setting our input(buffer) to only take 255 chars(bytes)*/
buffer = malloc(sizeof(char) * 255);
/**Recieves the Input from STDIN(input) and feeds it to buffer and n */
check = (getline(&buffer, &n, stdin));
/**Pretty much for if the user hits enter without typing anything*/
if (check == -1)
{
	free(buffer);
	return (NULL);
}
/**If the buffer is empty*/
if (buffer[0] == '\n' && buffer[1] == '\0')
	/**Stop(command terminator)*/
	;
else
{
	/**strtok splits the input at new_line variable*/
	buffer = strtok(buffer, new_line);
	/**checking for our only_spaces function and fills in accordingly*/
	if ((is_only_spaces(buffer)))
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

int is_only_spaces(char *string)
{
/**For the index of string*/
int i = 0;

while (string[i] != '\0')
{
	/**ASCII 32 = " ", This checks if this is all string is*/
	if (string[i] != 32)
	return (FALSE);
	i++;
}
return (TRUE);
}
/**
* split_string - Splits the string
* @string_to_split: - The string we are breaking up
* @delimiter: where we are breaking the string up
* Return: A double pointer which is a list of strings split up
*/
char **split_string(char *string_to_split, char *delimiter)
{
char **ret_array;
int i = 0, j = 0, k = 0, b = 0;
int length = strlen(string_to_split);
int num_of_tokens = 0;
int delimiter_length = strlen(delimiter);
/** Counts the number of tokens*/
for (i = 0; i < length; i++)
{
  if (strncmp(&string_to_split[i], delimiter, delimiter_length) == 0)
  {
    num_of_tokens++;
    i += delimiter_length - 1; /**skips delimiter*/
  }
}
/**for the last token*/
num_of_tokens++;

ret_array = malloc(sizeof(char *) * (num_of_tokens + 1));
if (ret_array == NULL)
{
  return (NULL);
}
/**Allocates memory for each token into array*/
for (i = 0, k = 0; i < length; i++)
{
  if (strncmp(&string_to_split[i], delimiter, delimiter_length) == 0)
  {
    ret_array[k] = malloc(sizeof(char) * (i - j + 1));
    if (ret_array[k] == NULL)
    {
      for (b = 0; b < k; b++)
      {
        free(ret_array[b]);
      }
      free(ret_array);
      return (NULL);
    }
    strncpy(ret_array[k], &string_to_split[j], i - j);
    ret_array[k][i - j] = '\0';
    k++;
    i += delimiter_length - 1;
    j = i + 1;
  }
}
ret_array[k] = malloc(sizeof(char) * (length - j + 1));
if (ret_array[k] == NULL)
{
  for (b = 0; b <= k; b++)
  {
    free(ret_array[b]);
  }
  free(ret_array);
  return (NULL);
}
strncpy(ret_array[k], &string_to_split[j], length -j);
ret_array[k][length - j] = '\0';
k++;
ret_array[k] = NULL;
return ret_array;
}
/**
* num_of_spaces - Gets length of buckets to allocate data from a string delim
* @string: The string to evalute
* @delimiter: The string that is breaking up str
* Return: The number of spaces to store the data, trailing NULL excluded
*/
int num_of_spaces(char *string, char *delimiter)
{
/**variables for the index*/
int i = 0;

/**count is for the delimiters*/
int count = 1;

/**indicates if space is found*/
int has_space = TRUE;

/**The first delimiter*/
char delim = delimiter[0];

/**Checks for empty *string or NULL*/
if (string[i] == '\0' || string == NULL)
	return (0);

while (string[i] != '\0')
{
	if (string[i] == delim)
	{
	/**If the first charachter isnt a delimiter(space)*/
	if (has_space == 0)
	{
		count++;
		has_space = TRUE;
	}
	}
	else
	has_space = FALSE;
	i++;
}
/**Number of delims returned*/
return (count);
}
