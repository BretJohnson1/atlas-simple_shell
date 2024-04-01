#include "shell.h"
/**
 * *_strcat - meows 2 strings together
 * @dest: where big string goes and other smol string comes
 * @src: smol string input
 * Return: big string
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;
/** find the end of the destination string*/
	while (dest[i])
	{
		i++;
	}
/** concatenate the source string and the destination string*/
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
/** add NULL terminator and return pointer to new string*/
	dest[i] = '\0';
	return (dest);
}
/**
 * *_strcpy - function for to copy chararr
 * @src: source of chararr
 * @dest: destination of chararr
 * Return: finaldestination
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;
/** copy characters from src to dest until NULL*/
	while (*(src + a))
	{
/** copy characters and increment through*/
		*(dest + a) = *(src + a);
		a++;
	}
/** add NULL to mark end of string and return pointer to string*/
	dest[a] = '\0';
	return (dest);
}
/**
 * _strcmp - compares strings ASCII values
 * @s1: first string
 * @s2: second string
 * Return: first dif
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0, dif = 0;
/** loop until NULL or characters dont match*/
	while (s1[i] && s2[i])
	{
/** check if the characters of both strings are equal*/
		if (s1[i] == s2[i])
		{
			i++;
			continue;
		}
		else
		{
/** calculate difference in ASCII values*/
			dif = s1[i] - s2[i];
			break;
		}
	}
/** return the difference inn ASCII values*/
	return (dif);
}
/**
 * _strlen - function to find length of string
 * @s: string input
 * Return: string length
 */
int _strlen(char *s)
{
	int a = 0;
/** loop until reaching the NULL terminator*/
	while (*(s + a) != '\0')
	{
		a++;
	}
	return (a);
}
/**
 * _strncmp - compares strings up to n chars
 * @s1: first string
 * @s2: second string
 * @n: num of chars to compare
 * Return: first dif or 0 if none
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i = 0, dif = 0;
/** loop until reaching the end of either strings or until strings are compared*/
	while (s1[i] && s2[i] && (i < n))
	{
/** compare characters at the same index*/
		if (s1[i] == s2[i])
		{
			i++;
			continue;
		}
		else
		{
/** calculate the difference between the characters*/
			dif = s1[i] - s2[i];
			break;
		}
	}
/** return the difference between the characters*/
	return (dif);
}
