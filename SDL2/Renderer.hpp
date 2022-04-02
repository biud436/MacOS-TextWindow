//
//  Renderer.hpp
//  SDL2
//
//  Created by 어진석 on 2022/04/02.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <SDL.h>
#include <SDL_ttf.h>

typedef struct _MyPoint {
    int x;
    int y;
    const char* text;
} MyPoint;

class Renderer
{
public:
    static Renderer* s_pInstance;
    static Renderer& GetInstance();
public:
    bool Prepare();
    void RenderLoop();
    void Destroy();
    
    void GetTextAndRect(SDL_Renderer* renderer, int x, int y, const char* text, TTF_Font *font, SDL_Texture **texture, SDL_Rect* rect);
protected:
    SDL_Window* _pWindow;
    SDL_Renderer* _pRenderer;
    SDL_Surface* _pSurface;
    TTF_Font* _pFont;
private:
    SDL_Texture* _pTexture;
    SDL_Rect* _pRect;
    bool _isRunning;
    MyPoint _myPoint;
    int _acc;
private:
    Renderer();
    virtual ~Renderer();
    Renderer(const Renderer&);
    Renderer& operator=(const Renderer&);
};

#endif /* Renderer_hpp */
