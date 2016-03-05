#include <stdio.h>
#include <stdlib.h>

const char* TrimLeft(const char *str)
{
	if (*str == '\0')
		return str;

	if (*str == ' ' || *str == '\t')
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
