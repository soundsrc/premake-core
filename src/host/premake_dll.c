/**
 * \file   premake_dll.c
 * \brief  Program entry point.
 * \author Copyright (c) 2002-2013 Jason Perkins and the Premake project
 */

#include <stdio.h>

extern int main(int argc, const char** argv);


#if _WIN32
#	define PREMAKE_DLLEXPORT __declspec(dllexport)
#else
#	define PREMAKE_DLLEXPORT __attribute__ ((visibility ("default")))
#endif

PREMAKE_DLLEXPORT
int runPremake(const char *path, const char *action)
{

	char fileParam[1024];

	if (snprintf(fileParam, sizeof(fileParam), "--file=%s", path) >= (int)sizeof(fileParam))
	{
		fprintf(stderr, "Input path '%s' is too long.\n", path);
		return -1;
	}

	const char *argv[] =
	{
		"premake",
		fileParam,
		action
	};

	return main(3, argv);
}
