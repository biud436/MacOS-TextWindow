//
//  Constants.h
//  SDL2
//
//  Created by 어진석 on 2022/04/03.
//

#pragma once
#ifndef Constants_h
#define Constants_h

namespace RS::PLATFORM {
#ifdef _WIN64
#define RS_PLATFORM "win64"
#define RS_WINDOWS
#elif _WIN32
#define RS_PLATFORM "win32"
#define RS_WINDOWS
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
        // iOS Simulator
#define RS_PLATFORM "iphone"
#define RS_IOS
#elif TARGET_OS_IPHONE
        // iOS device
#define RS_PLATFORM "iphone"
#define RS_IOS
#elif TARGET_OS_MAC
        // Other kinds of Mac OS
#define RS_PLATFORM "mac"
#define RS_OSX
#else
#   error "Unknown Apple platform"
#endif
#elif __linux__
#define RS_PLATFORM "linux"
#define RS_LINUX
#elif __unix
#define RS_PLATFORM "unix"
#define RS_UNIX
#elif __ANDROID__
#define RS_PLATFORM "android"
#define RS_ANDROID
#elif __posix
#define RS_PLATFORM "posix"
#define RS_POSIX
#endif
    
    static const char* type = RS_PLATFORM;
    
}

#include <string>

const std::string WINDOW_NAME("test");
const std::string CLASS_NAME("test");
const int WINDOW_WIDTH = 768;
const int WINDOW_HEIGHT = 896;
const std::string LINE_BREAK("\r\n");

typedef float IFLOAT;

const IFLOAT FPS1 = 240.0f;
const IFLOAT FPS2 = 10.0f;
const IFLOAT MIN_FRAME_TIME = 1.0f / FPS1;
const IFLOAT MAX_FRAME_TIME = 1.0f / FPS2;
const IFLOAT MS_PER_UPDATE = 1.0f / 60.0f;

/**
* @def PI
*/
const IFLOAT PI = 3.141592653589793f;

// @def SPRITE_SHEET_COLS
const int SPRITE_SHEET_COLS = 4;

// @def SPRITE_SHEET_ROWS
const int SPRITE_SHEET_ROWS = 4;

#define RS_D3D9 true

/**
* @def SAFE_DELETE(p)
*/
#define SAFE_DELETE(p) {\
    if(( p )!=nullptr) { \
        delete (p); \
        ( p )=nullptr; \
    } \
}

#endif /* Constants_h */
