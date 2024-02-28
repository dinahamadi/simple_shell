#include "mainshell.h"

/**
 * int_to_str - Converts a positive integer into a string
 * @n: The integer to be converted
 * @s: The buffer to store the string
 * Return: A pointer to the string s
 */
char  *int_to_str(int n, char *s)
{
	int i = 0;

	while (n > 0)
	{
		int digit = n % 10;
		char c = digit + '0';

		s[i] = c;
		i++;
		n = n / 10;
	}
	s[i] = '\0';
	reverse_str(s);
	return (s);
}

/**
 * reverse_str - Reverses a string in place
 * @s: The string to be reversed
 * Return: a reversed string.
 */
void reverse_str(char *s)
{
	char *start = s;
	char *end = s + strlen(s) - 1;

	while (start < end)
	{
		char temp = *start;

		*start = *end;
		*end = temp;
		start++;
		end--;
	}
}
