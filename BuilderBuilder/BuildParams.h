#ifndef __BB_BUILD_PARAM_H__
#define __BB_BUILD_PARAM_H__

typedef struct InitParam
{
	char symbol[256];
	char type[256];
} INIT_PARAM;

typedef struct InitParamList
{
	int cap;
	int count;
	INIT_PARAM params[1];
} INIT_PARAM_LIST;

typedef struct BuildParams
{
	char className[256];
	INIT_PARAM_LIST *initParams;
} BUILD_PARAMS;

int InitBuildParams(BUILD_PARAMS *params, FILE *fp);
void FreeBuildParams(BUILD_PARAMS *params);

#endif
