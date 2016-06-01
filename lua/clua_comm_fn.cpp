// Copyright (C) 2016 - XuKoo Inc.
// Author: davidluan
// CreateTime: 2016-05-31

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
};

class   CLuaFun
{
public:
    CLuaFun(void);
    ~CLuaFun(void);


    void Init();
    void Close();


    bool LoadLuaFile(const char* pfile_name);
    bool CallLuaFn(const char* pfun_name, int param1, int param2);


private:
    lua_Status * _pstate;
};


void CLuaFun::Init()
{
    if(!_pstate)
    {
        _pstate = luaL_newstate();
        luaL_openlibs(_pstate);
    }
}

bool CLuaFun::LoadLuaFile(const char* pfile_name)
{
    if(!_pstate)
    {
        printf("CLuaFun:: _pstate is null\n");
        return false;
    }

    int iret = luaL_dofile(_pstate, pfile_name);

    if(0!=iret )
    {
        printf("CLuaFun:: luaL_dofile iret = %d\n", iret);
        return false;
    }
    int result = lua_pcall(_pstate, 0, 0, 0);

    return result==0;

}

void CLuaFun::Close()
{
    if(_pstate)
    {
        lua_close(_pstate);
        _pstate =NULL;
    }
}



int main(int argc, const char *argv[])
{

    CLuaFun luafn =  CLuaFun();

    luafn.
    return 0;

}
