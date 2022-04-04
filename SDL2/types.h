//
//  types.h
//  SDL2
//
//  Created by 어진석 on 2022/04/04.
//

#ifndef types_h
#define types_h

typedef unsigned char BYTE;
typedef struct tagRECT {
    unsigned long left;
    unsigned long top;
    unsigned long right;
    unsigned long bottom;
} RECT, *PRECT, *NPRECT, *LPRECT;

#endif /* types_h */
