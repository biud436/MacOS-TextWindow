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

SDL_Color textColor = {255, 255, 255};

Renderer* Renderer::s_pInstance = 0;

Renderer& Renderer::GetInstance()
{
    static Renderer *s_pInstance = new (std::nothrow) Renderer();
    
    return *s_pInstance;
}

Renderer::Renderer():
    _pWindow(0),
    _pRenderer(0),
    _pSurface(0),
    _pFont(0),
    _pTexture(0),
    _pRect(new SDL_Rect()),
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
    delete _pRect;
}

bool Renderer::Prepare()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        _pWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
        
        if(_pWindow != 0) {
            _pRenderer = SDL_CreateRenderer(_pWindow, -1, 0);
        }
    } else {
        return false;
    }
    
    // Initialize the true type font.
    if (TTF_Init() == -1) {
        return false;
    }
        
    _pFont = TTF_OpenFont("/Library/Fonts/NanumGothic.ttf", 22);
    
    _isRunning = true;
    
    GetTextAndRect(_pRenderer, _myPoint.x, _myPoint.y, _myPoint.text, _pFont, &_pTexture, _pRect);
    
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
        SDL_SetRenderDrawColor(_pRenderer, 255, 255, 255, 255);
        SDL_RenderClear(_pRenderer);
        
        _myPoint.x = input.getMouseX();
        _myPoint.y = input.getMouseY();
        
        // Get the width of text rect.
        GetTextAndRect(_pRenderer, _myPoint.x, _myPoint.y, _myPoint.text, _pFont, &_pTexture, _pRect);
        
        // Move around the text.
        if(_myPoint.x > 640 - _pRect->w || _myPoint.x < 0) {
            _acc *= -1;
        }
        
        _myPoint.x += _acc;
        
        GetTextAndRect(_pRenderer, _myPoint.x, _myPoint.y, _myPoint.text, _pFont, &_pTexture, _pRect);
        
        // Draw default screen render texture.
        SDL_RenderCopy(_pRenderer, _pTexture, 0, _pRect);
        
        // Update screen
        SDL_RenderPresent(_pRenderer);
    }
}

void Renderer::Destroy()
{
    SDL_DestroyTexture(_pTexture);
    SDL_DestroyRenderer(_pRenderer);
    SDL_DestroyWindow(_pWindow);
    
    TTF_CloseFont(_pFont);
    TTF_Quit();
    
    SDL_Quit();
}

void Renderer::GetTextAndRect(SDL_Renderer* renderer, int x, int y, const char* text, TTF_Font *font, SDL_Texture **texture, SDL_Rect* rect) {
    int textWidth;
    int textHeight;
    
    SDL_Surface *surface;
    SDL_Color textColor = {0, 0, 0, 0};
    
    surface = TTF_RenderUTF8_Blended(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    
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
