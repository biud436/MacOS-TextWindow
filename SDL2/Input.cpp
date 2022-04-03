//
//  Input.cpp
//  SDL2
//
//  Created by 어진석 on 2022/04/02.
//

#include "Input.hpp"
#include "App.hpp"
#include <SDL.h>


Input* Input::s_pIstance = 0;


Input::Input():
    _mouse(0.0f, 0.0f),
    _mouseWheel(0)
{
    initialize();
}

Input::~Input()
{
    
}

void Input::initialize()
{
    for(int i = 0; i < 3; i++)
    {
        _mouseStates.push_back(false);
    }
    SDL_PumpEvents();
    _keyOldStates = const_cast <Uint8*>(SDL_GetKeyboardState(0));
    _keyCurrentStates = const_cast <Uint8*>(SDL_GetKeyboardState(0));
    _mouse.setX(0.0f);
    _mouse.setY(0.0f);
}

Input& Input::GetInstance()
{
    if(s_pIstance == 0)
    {
        s_pIstance = new Input();
    }
    
    return *s_pIstance;
}

void Input::onMouseButtonDown(SDL_Event& event)
{
    switch (event.button.button)
    {
        case SDL_BUTTON_LEFT:
            _mouseStates[LEFT] = true;
            break;
        case SDL_BUTTON_MIDDLE:
            _mouseStates[MIDDLE] = true;
            break;
        case SDL_BUTTON_RIGHT:
            _mouseStates[RIGHT] = true;
        default:
            break;
    }
}

void Input::onMouseButtonUp(SDL_Event& event)
{
    switch (event.button.button)
    {
        case SDL_BUTTON_LEFT:
            _mouseStates[LEFT] = false;
            break;
        case SDL_BUTTON_MIDDLE:
            _mouseStates[MIDDLE] = false;
            break;
        case SDL_BUTTON_RIGHT:
            _mouseStates[RIGHT] = false;
        default:
            break;
    }
}

bool Input::isKeyDown(SDL_Keycode vKey) const
{
    return _keyCurrentStates[SDL_GetScancodeFromKey(vKey)];
}

bool Input::isKeyDown(SDL_Scancode vKey) const
{
    return _keyCurrentStates[vKey] == KB_DOWN;
}

bool Input::isKeyUp(SDL_Keycode vKey) const
{
    return _keyCurrentStates[SDL_GetScancodeFromKey(vKey)] == KB_UP;
}

bool Input::isKeyUp(SDL_Scancode vKey) const
{
    return _keyCurrentStates[vKey] == KB_UP;
}

bool Input::isKeyPress(SDL_Keycode vKey) const
{
    return _keyCurrentStates[SDL_GetScancodeFromKey(vKey)] == KB_DOWN;
}

bool Input::isKeyPress(SDL_Scancode vKey) const
{
    return _keyCurrentStates[vKey] == KB_DOWN;
}

bool Input::isAnyKeyDown() const
{
    for(int i = SDL_SCANCODE_A;
        i < SDL_NUM_SCANCODES; i++)
    {
        if(_keyCurrentStates[i] == KB_DOWN)
            return true;
    }
           
    return false;
}


void Input::onKeyboardUpdate()
{
    memcpy(_keyOldStates, _keyCurrentStates, sizeof(_keyOldStates));
    
    _keyCurrentStates = const_cast <Uint8*>(SDL_GetKeyboardState(0));
}

void Input::onUpdateMousePositon(SDL_Event& event)
{
    _mouse.setX(event.motion.x);
    _mouse.setY(event.motion.y);
}

/**
* 마우스 X 좌표 반환합니다.
*/
float Input::getMouseX()
{
    return _mouse.getX();
}

/**
* 마우스 Y 좌표 반환합니다.
*/
float Input::getMouseY()
{
    return _mouse.getY();
}

/**
* 특정 마우스 버튼을 눌렀는 지 확인합니다.
*/
bool Input::isMouseDown(MouseButton state) const
{
    return _mouseStates[state];
}

/**
* 특정 마우스 버튼을 눌렀다가 뗐는 지 확인합니다.
*/
bool Input::isMouseUp(MouseButton state) const
{
    return !_mouseStates[state];
}

/**
* 특정 마우스 버튼을 눌린 상태인지 확인합니다.
*/
bool Input::isMousePress(MouseButton state) const
{
    return isMouseDown(state);
}

/**
* 아무 마우스 버튼이나 눌렀는 지 확인합니다.
*/
bool Input::isAnyMouseDown() const
{
    for(int i = 0; i < 3; i++)
    {
        if(_mouseStates[i]) {
            return true;
        }
    }
    
    return false;
}

/**
* 마우스 휠 값을 확인합니다.
*/
int Input::getMouseZ() const
{
    return 0;
}

/**
* 마우스 휠 값을 설정합니다.
*/
void Input::setMouseZ(int value)
{
    if(value < 0) {
        value = -1;
    }
    if(value > 0) {
        value = 1;
    }
    _mouseWheel = value;
}

void Input::onMouseWheel(SDL_Event& event)
{
    setMouseZ(event.wheel.y);
}

void Input::update()
{
    SDL_Event event;
    
    while(SDL_PollEvent(&event))
    {
        onKeyboardUpdate();

        switch(event.type)
        {
            case SDL_QUIT:
                App::GetInstance().Quit();
                break;
            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event);
                break;
            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event);
                break;
            case SDL_MOUSEWHEEL:
                onMouseWheel(event);
                break;
            case SDL_MOUSEMOTION:
                onUpdateMousePositon(event);
                break;
            default:
                break;
        }
    }
}
