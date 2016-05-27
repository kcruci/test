#include<iostream>
using namespace std;
#include<stdio.h>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
lua_State* L;
static int average(lua_State *L)
{
	//返回栈中元素的个数
	int n = lua_gettop(L);
	double sum = 0;
	int i;
	for (i = 1; i <= n; i++)
	{
		if (!lua_isnumber(L, i)) 
		{
			lua_pushstring(L, "Incorrect argument to 'average'");
			lua_error(L);
		}
		sum += lua_tonumber(L, i);
	}
	/* push the average */
	lua_pushnumber(L, sum / n);
	/* push the sum */
	lua_pushnumber(L, sum);

	/* return the number of results */
	return 2;
}
int main (int argc,char*argv[])
{
	/* initialize Lua */
	L = luaL_newstate();
	/* load Lua libraries */
	luaL_openlibs(L);
	/* register our function */
	lua_register(L, "average", average);
	/* run the script */
	luaL_dofile(L, "lua_call.lua");

	lua_getglobal(L,"avg");
	//cout<<"avg is:"<<lua_tointeger(L,-1)<<endl;
	lua_pop(L,1);
	lua_getglobal(L,"sum");
	//cout<<"sum is:"<<lua_tointeger(L,-1)<<endl;
	/* cleanup Lua */
	lua_close(L);

	return 0;
}
//程序
//*lua_gettop()的作用是返回栈顶元素的序号. 由于Lua的栈是从1开始编号的,
// 所以栈顶元素的序号也相当于栈中的元素个数. 在这里, 栈中元素的个数就
// 是传入的参数个数.
//* for循环计算所有传入参数的总和. 这里用到了数值转换lua_tonumber().
//* 然后偶们用lua_pushnumber()把平均值和总和push到栈中.
//* 最后, 偶们返回2, 表示有两个返回值.
//* 虽然在C++中定义了average()函数, 但Lua程序并不知道, 所以需
//  要在main函数中加入
//     // register our function 
//  lua_register(L, "average", average);
//　　这两行的作用就是告诉e15.lua有average()这样一个函数.
//* 这个程序可以存成cpp也可以存成c, 如果以.c为扩展名就不需要加extern "C"
//   　　
//编译的方法偶们上次说过了, 方法相同.
//e15.lua执行的方法只能用上例中的C++中执行, 而不能用命令行方式执行.*/

