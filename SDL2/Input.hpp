//
//  Input.hpp
//  SDL2
//
//  Created by 어진석 on 2022/04/02.
//

#ifndef Input_hpp
#define Input_hpp

#include <stdio.h>
#include <vector>
#include <SDL.h>
#include "Vector2D.hpp"

enum MouseButton {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

/**
 * Note: 키 눌림은 키가 눌리지 않음, 키 눌림, 키 뗌, 키가 계속 눌림 등 4가지 상태로 구분합니다.
 */
enum KEY_STATE
{
//    KB_NONE = 0,
    KB_UP = 0,
    KB_DOWN = 1,
//    KB_PRESS = 3
};

class Input
{
public:
    
    static Input* s_pIstance;

    /**
    * 입력 모듈을 초기화합니다.
    */
    void initialize();
    
    static Input& GetInstance();

    /**
    * 입력 모듈을 업데이트합니다.
    */
    void update();

    /**
    * 특정 키가 눌렸는 지 확인합니다.
    */
    bool isKeyDown(SDL_Scancode vKey) const;

    /**
    * 특정 키를 눌렀다가 뗐는 지 확인합니다.
    */
    bool isKeyUp(SDL_Scancode vKey) const;

    /**
    * 특정 키가 눌린 상태 인지 확인합니다.
    */
    bool isKeyPress(SDL_Scancode vKey) const;

    /**
    * 아무 버튼이나 눌렀는 지 확인합니다.
    */
    bool isAnyKeyDown() const;

    /**
    * 마우스 X 좌표 반환합니다.
    */
    float getMouseX();

    /**
    * 마우스 Y 좌표 반환합니다.
    */
    float getMouseY();

    /**
    * 특정 마우스 버튼을 눌렀는 지 확인합니다.
    */
    bool isMouseDown(MouseButton state) const;

    /**
    * 특정 마우스 버튼을 눌렀다가 뗐는 지 확인합니다.
    */
    bool isMouseUp(MouseButton state) const;

    /**
    * 특정 마우스 버튼을 눌린 상태인지 확인합니다.
    */
    bool isMousePress(MouseButton state) const;

    /**
    * 아무 마우스 버튼이나 눌렀는 지 확인합니다.
    */
    bool isAnyMouseDown() const;

    /**
    * 마우스 휠 값을 확인합니다.
    */
    int getMouseZ() const;

    /**
    * 마우스 휠 값을 설정합니다.
    */
    void setMouseZ(int value);
    
private:
    
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);
    void onUpdateMousePositon(SDL_Event& event);
    void onKeyboardUpdate();
    void onMouseWheel(SDL_Event& event);

    std::vector<bool> _mouseStates;
    Uint8* _keyCurrentStates;
    Uint8* _keyOldStates;
    
    Vector2D _mouse;
    int _mouseWheel;

private:
    Input();
    virtual ~Input();
    Input(const Input&);
    void operator=(const Input&);
};


#endif /* Input_hpp */
