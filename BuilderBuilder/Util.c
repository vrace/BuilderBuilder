#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const char* TrimLeft(const char *str)
{
	if (*str == '\0')
		return str;

	if (*str == ' ' || *str == '\t' || *str == '\n')
		return TrimLeft(str + 1);

	return str;
}

int FileExists(const char *file)
{
	FILE *fp;
	int exist;

	fp = fopen(file, "rb");
	if (fp)
	{
		exist = 1;
		fclose(fp);
	}
	else
	{
		exist = 0;
	}
	
	return exist;
}

void StrcpyUntilAny(char *dest, const char *str, const char *control)
{
	const char *end;

	assert(dest != NULL);
	assert(str != NULL);
	assert(control != NULL);

	end = strpbrk(str, control);
	if (end)
	{
		int size = end - str;
		strncpy(dest, str, size);
		dest[size] = '\0';
	}
	else
	{
		strcpy(dest, str);
	}
}
