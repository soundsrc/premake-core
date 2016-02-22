/**
 * \file   premake_main.c
 * \brief  Program entry point.
 * \author Copyright (c) 2002-2013 Jason Perkins and the Premake project
 */
#ifdef __OpenBSD__
#  include <stdlib.h>
#  include <unistd.h>
#  include <sys/param.h>
#endif
#include "premake.h"

int main(int argc, const char** argv)
{
	lua_State* L;
	int z;

#ifdef OpenBSD5_9
	if(pledge("stdio rpath wpath cpath exec proc"
#ifdef PREMAKE_CURL
		" inet"
#endif
		, NULL) < 0) {
		perror("premake5");
		exit(-1);
	}
#endif

	L = luaL_newstate();
	luaL_openlibs(L);

	z = premake_init(L);
	if (z == OKAY) {
		z = premake_execute(L, argc, argv, "src/_premake_main.lua");
	}

	lua_close(L);
	return z;
}
