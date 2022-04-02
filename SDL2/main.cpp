//
//  main.cpp
//  SDL2
//
//  Created by 어진석 on 2021/06/27.
//

#include <iostream>
#include <exception>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <unistd.h>
#include <limits.h>
#include <wchar.h>

#include "App.hpp"
#include "Renderer.hpp"

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

int Lua_Init()
{
    lua_State *l = luaL_newstate();
    luaL_openlibs(l);
    
    luaL_dostring(l, "print 'hello'");
    
    lua_close(l);

    return 0;
}



int main(int argc, const char * argv[]) {
    

    App& app = App::GetInstance();
    
    std::cout << app.GetCurrentDirectory() << std::endl;
    std::cout << app.GetWorkingDirectory() << std::endl;
    
    Lua_Init();
    
    app.EnumDirectories();
    
    Renderer& renderer = Renderer::GetInstance();
    if(renderer.Prepare()) {
        renderer.RenderLoop();
        renderer.Destroy();
    }
    
    return 0;
}
