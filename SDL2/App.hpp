//
//  App.hpp
//  SDL2
//
//  Created by 어진석 on 2022/04/02.
//

#ifndef App_hpp
#define App_hpp

#include <cstdio>
#include <string>

class App
{
public:
    static App* s_pInstance;
    static App& GetInstance();
public:
    void Start();
    void Quit();
    
    std::string GetCurrentDirectory();
    std::string GetWorkingDirectory();
    std::string GetBaseDirectory();
    void EnumDirectories();
private:
    App();
    virtual ~App();
    App(const App&);
    App& operator=(const App&);
};

#endif /* App_hpp */
