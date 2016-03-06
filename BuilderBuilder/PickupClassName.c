#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "PickupClassName.h"
#include "Util.h"

#define STATE_CLASS 0
#define STATE_NAME 1
#define STATE_DONE 2

static const char KEYWORD_CLASS[] = "class";

int PickupClassNameFromLine(char *buf, const char *line)
{
	int state = STATE_CLASS;

	assert(buf != NULL);
	assert(line != NULL);

	while (line && *line && state <= STATE_NAME)
	{
		switch (state)
		{
		case STATE_CLASS:
			line = TrimLeft(line);

			if (strstr(line, KEYWORD_CLASS) == line)
			{
				const char *delimiter;

				line += strlen(KEYWORD_CLASS);
				delimiter = strpbrk(line, " \t\n");

				if (line == delimiter)
				{
					state = STATE_NAME;
				}
				else
				{
					line = delimiter;
				}
			}
			else
			{
				line = strpbrk(line, " \t\n");
			}
			break;

		case STATE_NAME:
			line = TrimLeft(line);
			StrcpyUntilAny(buf, line, " \t\n:{<");
			state = STATE_DONE;
			break;

		default:
			break;
		}
	}

	return state == STATE_DONE && strlen(buf) != 0;
}
