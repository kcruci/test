#include <stdio.h>
extern "C"{

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

lua_State* L;

int luaadd(int x,int y)
{
	int sum(0);
	lua_getglobal(L, "add");
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	lua_call(L, 2, 1);

	sum = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);
	return sum;
}


int main ( int argc, char *argv[] )
{
	int sum;
	/* initialize Lua */
	L = luaL_newstate();
	/* load Lua base libraries */
	luaL_openlibs(L);
	/* load the script */
	luaL_dofile(L, "lua_fun.lua");
	/* call the add function */
	sum = luaadd( 10, 15 );
	/* print the result */
	printf( "The sum is %d\n", sum );
	/* cleanup Lua */
	lua_close(L);
	return 0;
}
