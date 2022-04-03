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
    
    void GetTextAndRect(int x, int y, const char* text, TTF_Font *font, SDL_Texture **texture, SDL_Rect* rect);
    
    void requestDestroy();

protected:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    SDL_Surface* _surface;
    TTF_Font* _font;
private:
    SDL_Texture* _texture;
    SDL_Rect* _rect;
    MyPoint _myPoint;
    int _acc;
    bool _isRunning;
private:
    Renderer();
    virtual ~Renderer();
    Renderer(const Renderer&);
    Renderer& operator=(const Renderer&);
};

#endif /* Renderer_hpp */
