//
//  Renderer.cpp
//  SDL2
//
//  Created by 어진석 on 2022/04/02.
//

#include "Renderer.hpp"
#include <iostream>
#include <exception>
#include <thread>
#include <string>
#include <wchar.h>
#include <unistd.h>
#include <limits.h>
#include "Input.hpp"
#include "File.hpp"

SDL_Color textColor = {255, 255, 255};

Renderer* Renderer::s_pInstance = 0;

Renderer& Renderer::GetInstance()
{
    static Renderer *s_pInstance = new (std::nothrow) Renderer();
    
    return *s_pInstance;
}

Renderer::Renderer():
    _window(0),
    _renderer(0),
    _surface(0),
    _font(0),
    _texture(0),
    _rect(new SDL_Rect()),
    _isRunning(false),
    _acc(1)
{
    // initialize rect
    _myPoint.x = 0;
    _myPoint.y = 0;
    _myPoint.text = "안녕하십니까";
}

Renderer::~Renderer()
{
    delete _rect;
}

bool Renderer::Prepare()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        _window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
        
        if(_window != 0) {
            _renderer = SDL_CreateRenderer(_window, -1, 0);
        }
    } else {
        return false;
    }
    
    // Initialize the true type font.
    if (TTF_Init() == -1) {
        return false;
    }
    
    std::string fileAbsolutePath = "/Library/Fonts/NanumGothic.ttf";
    
    SDL_assert(File::GetInstance().exists(fileAbsolutePath));
    
    _font = TTF_OpenFont(&fileAbsolutePath[0], 22);
    
    _isRunning = true;
    
    GetTextAndRect(_myPoint.x, _myPoint.y, _myPoint.text, _font, &_texture, _rect);
    
    return _isRunning;
}

void Renderer::RenderLoop()
{
    Input& input = Input::GetInstance();
    
    while(_isRunning) {
        
        input.update();
        
        // ESC를 눌렀을 때
        if(input.isKeyDown(SDL_SCANCODE_ESCAPE))
        {
            _isRunning = false;
        }
        
        // Clear screen
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
        SDL_RenderClear(_renderer);
        
        _myPoint.x = input.getMouseX();
        _myPoint.y = input.getMouseY();
        
        // Get the width of text rect.
        GetTextAndRect(_myPoint.x, _myPoint.y, _myPoint.text, _font, &_texture, _rect);
        
        // Move around the text.
        if(_myPoint.x > 640 - _rect->w || _myPoint.x < 0) {
            _acc *= -1;
        }
        
        _myPoint.x += _acc;
        
        // Draw default screen render texture.
        SDL_RenderCopy(_renderer, _texture, 0, _rect);
        
        // 메모리 누수 이슈 해결
        SDL_DestroyTexture(_texture);
        
        // Update screen
        SDL_RenderPresent(_renderer);
    }
}

void Renderer::Destroy()
{
    SDL_DestroyTexture(_texture);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    
    TTF_CloseFont(_font);
    TTF_Quit();
    
    SDL_Quit();
}

void Renderer::GetTextAndRect(int x, int y, const char* text, TTF_Font *font, SDL_Texture **texture, SDL_Rect* rect) {
    int textWidth;
    int textHeight;
    
    SDL_Surface *surface;
    SDL_Color textColor = {0, 0, 0, 0};
    
    surface = TTF_RenderUTF8_Blended(font, text, textColor);
    
    // Note: 메모리 관리 주의
    *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    
    textWidth = surface->w;
    textHeight = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = textWidth;
    rect->h = textHeight;
}

void Renderer::requestDestroy()
{
    _isRunning = false;
}
