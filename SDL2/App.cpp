//
//  App.cpp
//  SDL2
//
//  Created by 어진석 on 2022/04/02.
//

#include "App.hpp"
#include <thread>
#include <chrono>
#include <filesystem>
#include <unistd.h>
#include <limits.h>
#include <wchar.h>
#include <iostream>
#include <exception>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.hpp"

App* App::s_pInstance = 0;

App& App::GetInstance()
{
    static App *s_pInstance = new (std::nothrow) App();
    
    return *s_pInstance;
}

App::App()
{
    Start();
}

App::~App()
{
    Quit();
}

void App::Start()
{
    
}

void App::Quit()
{
    Renderer::GetInstance().requestDestroy();
}

/**
 *  현재 경로를 반환합니다.
 */
std::string App::GetCurrentDirectory() {
    std::string sBuffer;
    sBuffer.resize(PATH_MAX);
    getcwd(&sBuffer[0], sBuffer.size());
    
    return sBuffer;
}

std::string App::GetWorkingDirectory() {
    
    std::filesystem::path cwd = std::filesystem::current_path();
    
    return cwd.string();
}

void App::EnumDirectories() {
    std::filesystem::create_directory(GetWorkingDirectory());
    
    for(auto& p : std::filesystem::directory_iterator(GetWorkingDirectory())) {
        std::cout << p.path() << std::endl;
    }
}

std::string App::GetBaseDirectory()
{
    return SDL_GetBasePath();
}
