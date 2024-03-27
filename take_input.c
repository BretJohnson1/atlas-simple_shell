#include "simple_shell.h"

/** take-input - Takes input and makes it safe to process
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
	if (check == 1)
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
 * @string_to_split - The string we are breaking up
 * @delimiter: where we are breaking the string up
 * Return: A double pointer which is a list of strings split up
 */
char **split_string(char *string_to_split, char *delimiter)
{
	/**return for our array after modification*/
	char **ret_array;
	/**For the index(spot in array)*/
	int i = 0;
	/**length of the array using num_of_spaces, returns the amount of tokens = length*/
	long int length = num_of_spaces(string_to_split, delimiter);
	/**Copy from the STDIN(input)*/
	char copy_of_string[255];
	/**Next two are a must for strtok_r */
	char *save_pointer;
	char *grabtok;
/**Takes input from string_to_split pointer and stores in copy_of_string*/
	snprintf(copy_of_string, 255, "%s", string_to_split);
/**Memory allocated for a size by multiplying length times char(1) */
	ret_array = malloc(sizeof(char *) * (length + 1));
	/**So we can access the string for tokens from a copy_of_string*/
	save_pointer = copy_of_string;
/** Grabs the the tokens from the amount of length exmp(length equals four so grabtoks 4 times)*/
	for (i = 0; i < length; i++)
	{
		/**save_pointer = copy_of_string &save_pointer = */
		grabtok = strtok_r(save_pointer, delimiter, &save_pointer);
		ret_array[i] = malloc(sizeof(char) * 255);
		/**Allocating and storing each token from grabtok in an array index + 1*/
		snprintf(ret_array[i], 255, "%s", grabtok);
	}
	ret_array[i] = NULL;
	return (ret_array);
}
/**
 * num_of_spaces - Counts the number of buckets to allocate to store the data when given a string delimiter of the data
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
