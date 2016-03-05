#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Builder.h"
#include "Util.h"

FILE* OpenBuilderOutput(BUILD_PARAMS *params)
{
	char filename[1000];
	sprintf(filename, "%sBuilder.swift", params->className);

	if (FileExists(filename))
	{
		printf("The file '%s' already exists.\n", filename);
		return NULL;
	}
	else
	{
		FILE *fp = fopen(filename, "w");
		if (!fp)
			printf("Can't create file '%s'.\n", filename);

		return fp;
	}
}

int main(int argc, char *argv[])
{
	int code = 0;

	if (argc != 2)
	{
		printf("Usage: BuilderBuilder <source code file>\n");
		code = 1;
	}
	else
	{
		FILE *fp;

		fp = fopen(argv[1], "r");
		if (fp)
		{
			BUILD_PARAMS params;
			if (InitBuildParams(&params, fp))
			{
				FILE *dest;

				dest = OpenBuilderOutput(&params);
				if (dest)
				{
					BuildBuilder(&params, dest);
					fclose(dest);
				}
			}

			fclose(fp);
		}
		else
		{
			printf("Can't open source file '%s'\n", argv[1]);
			code = 2;
		}
	}

	return code;
}
