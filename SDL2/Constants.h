//
//  Constants.h
//  SDL2
//
//  Created by 어진석 on 2022/04/03.
//

#ifndef Constants_h
#define Constants_h

namespace RS {
    namespace PLATFORM {
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
    }
}

#endif /* Constants_h */
