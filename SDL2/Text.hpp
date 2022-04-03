//
//  Text.hpp
//  SDL2
//
//  Created by 어진석 on 2022/04/03.
//

#ifndef Text_hpp
#define Text_hpp

#include <string>

class Renderer;

class Text
{
public:
    Text();
    Text(std::string content);
    Text(const char* content);
    virtual ~Text();
    
    void render(Renderer* renderer);
    
protected:
    std::string _content;
};

#endif /* Text_hpp */
