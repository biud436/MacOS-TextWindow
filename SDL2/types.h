//
//  types.h
//  SDL2
//
//  Created by 어진석 on 2022/04/04.
//

#ifndef types_h
#define types_h

/**
 *  https://docs.microsoft.com/en-US/windows/win32/winprog/windows-data-types
 */
typedef unsigned char BYTE, *PBYTE, *LPBYTE;
typedef long LONG;
typedef float FLOAT, *PFLOAT;
typedef unsigned long DWORD, *PDWORD, *LPDWORD;
typedef DWORD COLORREF, *LPCOLORREF;
typedef int BOOL, *PBOOL, *LPBOOL;

typedef struct tagRECT
{
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT, *PRECT, *LPRECT;
typedef const RECT *LPCRECT;

typedef struct tagXFORM {
    FLOAT eM11;
    FLOAT eM12;
    FLOAT eM21;
    FLOAT eM22;
    FLOAT eDx;
    FLOAT eDy;
} XFORM, *PXFORM, *LPXFORM;

using TransformData = XFORM;

#endif /* types_h */
