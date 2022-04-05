//
//  TextureManager.hpp
//  SDL2
//
//  Created by 어진석 on 2022/04/05.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <map>
#include <string>
#include "Constants.hpp"
#include "UnCopyable.hpp"
#include "types.h"
#include <SDL.h>

using TransformData = XFORM;
using Color = COLORREF;

struct TextureData
{
    int width;
    int height;
    SDL_Texture* texture;
    TextureData();
    ~TextureData();
};

namespace Initial2D {

    class Color {
    public:
        BYTE red;
        BYTE green;
        BYTE blue;
        BYTE alpha;
        
        Color(BYTE r, BYTE g, BYTE b, BYTE a) :
            red(r),
            green(g),
            blue(b),
            alpha(a)
        {

        }
        
        void SetRGB(BYTE r, BYTE g, BYTE b)
        {
            red = r;
            green = g;
            blue = b;
        }

        void SetAlpha(BYTE a)
        {
            alpha = a;
        }

        COLORREF GetRGBColor() {
            return RGB(red, green, blue);
        }
    };
}


using TextureGroup = std::map<std::string, TextureData*>;

class TextureManager : private UnCopyable
{
public:
    TextureManager();
    virtual ~TextureManager();
public:

    
    bool Load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
    
    bool Remove(std::string id);

    void Draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer);

//    void DrawFrame(std::string id, int x, int y, int width, int height, RECT& rect, BYTE opacity, TransformData& transform, SDL_Renderer* pRenderer);
//
//    void DrawText(std::string id, int x, int y, int width, int height, RECT& rect, TransformData& transform, SDL_Renderer* pRenderer);

    bool valid(std::string id);

//    void DrawPoint(int x, int y);
//
//    void SetBitmapColor(BYTE r, BYTE g, BYTE b, BYTE a);

public:

    TextureGroup m_textureMap;
    Color        m_crTransparent;
    
    Initial2D::Color m_bitmapColor;
    
};


#endif /* TextureManager_hpp */
