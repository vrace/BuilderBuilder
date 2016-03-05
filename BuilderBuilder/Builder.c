#include <ctype.h>
#include <assert.h>
#include "Builder.h"

static void InjectParams(BUILD_PARAMS *params, FILE *fp)
{
	int i;
	INIT_PARAM *p;

	assert(params != NULL);
	assert(params->initParams != NULL);
	assert(fp != NULL);

	for (i = 0; i < params->initParams->count; i++)
	{
		p = &params->initParams->params[i];
		fprintf(fp, "    var %s: %s\n", p->symbol, p->type);
	}
}

static void InjectBuild(BUILD_PARAMS *params, FILE *fp)
{
	int i;

	assert(params != NULL);
	assert(params->initParams != NULL);
	assert(fp != NULL);

	fprintf(fp, "    func build() -> %s {\n", params->className);
	fprintf(fp, "        return %s(\n", params->className);
	for (i = 0; i < params->initParams->count; i++)
	{
		const char *symbol = params->initParams->params[i].symbol;
		fprintf(fp, "            %s: %s%c\n",
			symbol, symbol,
			i == params->initParams->count - 1 ? ')' : ',');
	}
	fprintf(fp, "    }\n");
}

static void InjectWithFuncs(BUILD_PARAMS *params, FILE *fp)
{
	int i;

	assert(params != NULL);
	assert(params->initParams != NULL);
	assert(fp != NULL);

	for (i = 0; i < params->initParams->count; i++)
	{
		INIT_PARAM *param = &params->initParams->params[i];

		fprintf(fp, "\n");
		fprintf(fp, "    func with%c%s(%s: %s) -> Self {\n",
			toupper(param->symbol[0]),
			&param->symbol[1],
			param->symbol, param->type);
		fprintf(fp, "        self.%s = %s\n", param->symbol, param->symbol);
		fprintf(fp, "        return self\n");
		fprintf(fp, "    }\n");
	}
}

void BuildBuilder(BUILD_PARAMS *params, FILE *fp)
{
	assert(params != NULL);
	assert(fp != NULL);

	fprintf(fp, "class %sBuilder {\n", params->className);
	InjectParams(params, fp);
	fprintf(fp, "\n");
	fprintf(fp, "    init() {\n");
	fprintf(fp, "        // TODO: initialize default values here\n");
	fprintf(fp, "    }\n");
	fprintf(fp, "\n");
	InjectBuild(params, fp);
	InjectWithFuncs(params, fp);
	fprintf(fp, "}\n");
}
