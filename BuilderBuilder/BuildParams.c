#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "BuildParams.h"
#include "Util.h"

static INIT_PARAM_LIST* InitParamListCreate(void)
{
	INIT_PARAM_LIST *list;

	list = malloc(sizeof(INIT_PARAM_LIST));
	assert(list != NULL);

	list->cap = 0;
	list->count = 0;

	return list;
}

static INIT_PARAM_LIST* InitParamListAppend(INIT_PARAM_LIST *list, const char *symbol, const char* type)
{
	INIT_PARAM *param;

	assert(list != NULL);
	assert(symbol != NULL);
	assert(type != NULL);

	if (list->count >= list->cap)
	{
		int increment = list->cap > 4 ? list->cap + list->cap / 2 : 4;
		list->cap += increment;
		list = realloc(list, sizeof(INIT_PARAM_LIST) + sizeof(INIT_PARAM) * list->cap);
		assert(list != NULL);
	}

	param = &list->params[list->count++];
	strcpy(param->symbol, symbol);
	strcpy(param->type, type);

	return list;
}

static INIT_PARAM_LIST* PickupParams(INIT_PARAM_LIST *list, char *str)
{
	char *symbol;
	char *type;
	static const char *initTag = "init(";
	static const char *delimiters = " :,)";

	assert(list != NULL);
	assert(str != NULL);

	str = strtok(str, delimiters);
	while (str && strlen(str) > 0 && str[0] != '{')
	{
		symbol = str;
		type = strtok(NULL, delimiters);

		if (symbol && type)
			list = InitParamListAppend(list, symbol, type);

		str = strtok(NULL, delimiters);
	}

	return list;
}

static INIT_PARAM_LIST* InitParamListFromLine(char *line)
{
	INIT_PARAM_LIST *list = NULL;
	char *str;
	static const char *initTag = "init(";

	str = (char*)TrimLeft(line);
	if (strstr(str, initTag) == str)
		list = PickupParams(InitParamListCreate(), str + strlen(initTag));

	return list;
}

static int ProcessClassDefine(BUILD_PARAMS *params, char *str)
{
	static const char *delimiters = " :{,";

	assert(params != NULL);
	assert(str != NULL);

	str = strstr(str, "class");
	if (str != NULL)
	{
		str = strtok(str + strlen("class"), delimiters);
		if (str != NULL)
			strcpy(params->className, str);
	}

	return str != NULL;
}

static int PickupClassName(BUILD_PARAMS *params, FILE *fp)
{
	char line[4096];
	int found = 0;

	assert(params != NULL);
	assert(fp != NULL);

	while (!found && fgets(line, 4096, fp))
		found = ProcessClassDefine(params, line);

	return found;
}

static int PickupInitParams(BUILD_PARAMS *params, FILE *fp)
{
	char line[4096];

	while (!params->initParams && fgets(line, 4096, fp))
		params->initParams = InitParamListFromLine(line);

	return params->initParams != NULL;
}

int InitBuildParams(BUILD_PARAMS *params, FILE *fp)
{
	int ret;

	params->className[0] = '\0';
	params->initParams = NULL;

	ret = PickupClassName(params, fp);
	if (ret)
		ret = PickupInitParams(params, fp);

	return ret;
}

void FreeBuildParams(BUILD_PARAMS *params)
{
	assert(params);

	free(params->initParams);
	params->initParams = NULL;
}
