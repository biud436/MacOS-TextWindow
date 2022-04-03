//
//  GameObject.hpp
//  SDL2
//
//  Created by 어진석 on 2022/04/03.
//

#ifndef GameObject_hpp
#define GameObject_hpp

class GameObject
{
public:
    GameObject();
    virtual ~GameObject() {}

    virtual void update(float elapsed);
    virtual void draw(void);
};


#endif /* GameObject_hpp */
