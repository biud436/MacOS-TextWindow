//
//  GameObject.hpp
//  SDL2
//
//  Created by 어진석 on 2022/04/02.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <SDL.h>
#include "Vector2D.hpp"

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    void render();

protected:
    // SDL_Texture _mainTexture;
    // SDL_Rect* _rect;
    // Vector2D _position;
};

#endif /* GameObject_hpp */
