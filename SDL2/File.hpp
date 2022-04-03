//
//  File.hpp
//  SDL2
//
//  Created by 어진석 on 2022/04/03.
//

#ifndef File_hpp
#define File_hpp

#include <SDL.h>
#include <string>

class File
{
public:
    static File* s_pInstance;
    static File& GetInstance();
public:
    bool exists(std::string filePath);
private:
    File();
    virtual ~File();
    File(const File&);
    File& operator=(const File&);
};

#endif /* File_hpp */
