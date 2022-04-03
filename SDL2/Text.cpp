//
//  Text.cpp
//  SDL2
//
//  Created by 어진석 on 2022/04/03.
//

#include "Text.hpp"
#include "Renderer.hpp"

Text::Text():
    _content("")
{
    
}

Text::Text(std::string content):
    _content(content)
{
    
}

Text::Text(const char* content):
    _content(content)
{
    
}

Text::~Text()
{
    
}


void Text::render(SDL_Renderer *renderer)
{
    
}
