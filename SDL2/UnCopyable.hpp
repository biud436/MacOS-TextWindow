//
//  UnCopyable.hpp
//  SDL2
//
//  Created by 어진석 on 2022/04/03.
//

#ifndef UnCopyable_hpp
#define UnCopyable_hpp

class UnCopyable {
public:
    UnCopyable() {}
    ~UnCopyable() {}
private:
    UnCopyable(const UnCopyable&);
    UnCopyable& operator=(UnCopyable&);
};

#endif /* UnCopyable_hpp */
