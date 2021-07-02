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
#include <filesystem>

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;
SDL_Surface* g_pSurface = 0;
TTF_Font* g_pFont = 0;

SDL_Color textColor = {255, 255, 255};

int Lua_Init()
{
    lua_State *l = luaL_newstate();
    luaL_openlibs(l);
    
    luaL_dostring(l, "print 'hello'");
    
    lua_close(l);

    return 0;
}

/**
 *  현재 경로를 반환합니다.
 */
std::string GetCurrentDirectory() {
    std::string sBuffer;
    sBuffer.resize(PATH_MAX);
    getcwd(&sBuffer[0], sBuffer.size());
    
    return sBuffer;
}

std::string GetWorkingDirectory() {
    
    std::filesystem::path cwd = std::filesystem::current_path();
    
    return cwd.string();
}

void EnumDirectories() {
    std::filesystem::create_directory(GetWorkingDirectory());
    
    for(auto& p : std::filesystem::directory_iterator(GetWorkingDirectory())) {
        std::cout << p.path() << std::endl;
    }
}

std::string GetBaseDirectory() {
    return SDL_GetBasePath();
}

void GetTextAndRect(SDL_Renderer* renderer, int x, int y, const char* text, TTF_Font *font, SDL_Texture **texture, SDL_Rect* rect) {
    int textWidth;
    int textHeight;
    
    SDL_Surface *surface;
    SDL_Color textColor = {0, 0, 0, 0};
    
    surface = TTF_RenderUTF8_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    textWidth = surface->w;
    textHeight = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = textWidth;
    rect->h = textHeight;
}

int main(int argc, const char * argv[]) {
    
    SDL_Texture *texture;
    SDL_Rect rect;
    
    Lua_Init();
    
    std::cout << GetCurrentDirectory() << std::endl;
    std::cout << GetWorkingDirectory() << std::endl;
    EnumDirectories();
    
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        g_pWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
        
        if(g_pWindow != 0) {
            g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
        }
    } else {
        return 1;
    }
    
    // Initialize the true type font.
    if (TTF_Init() == -1) {
        return 1;
    }
        
    g_pFont = TTF_OpenFont("/Library/Fonts/NanumGothic.ttf", 22);
    
    bool isRunning = true;
    
    GetTextAndRect(g_pRenderer, 0, 0, "안녕하세요", g_pFont, &texture, &rect);
    
    while(isRunning) {
        SDL_Event event;
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if( event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
            } else if(event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        
        SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
        SDL_RenderClear(g_pRenderer);
        
        SDL_RenderCopy(g_pRenderer, texture, NULL, &rect);
        
        SDL_RenderPresent(g_pRenderer);
    }
    
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(g_pRenderer);
    SDL_DestroyWindow(g_pWindow);
    
    TTF_CloseFont(g_pFont);
    TTF_Quit();
    
    SDL_Quit();
    
    return 0;
}
