//
//  File.cpp
//  SDL2
//
//  Created by 어진석 on 2022/04/03.
//

#include "File.hpp"

File* File::s_pInstance = nullptr;

File& File::GetInstance()
{
    if(s_pInstance == nullptr)
    {
        s_pInstance = new File();
    }
    
    return *s_pInstance;
}

File::File()
{
    
}

File::~File()
{
    
}

bool File::exists(std::string filePath)
{
    SDL_RWops* file = SDL_RWFromFile(&filePath[0], "r");
    
    if(file == 0)
    {
        return false;
    }
    
    SDL_RWclose(file);
    
    return true;
}
