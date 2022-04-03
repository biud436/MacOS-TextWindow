//
//  GameState.hpp
//  SDL2
//
//  Created by 어진석 on 2022/04/03.
//

#ifndef GameState_hpp
#define GameState_hpp

#include <string>
#include <vector>

class GameObject;

/**
 * @class GameState
 * @brief
 */
class GameState
{
public:

    /**
    * @fn        update
    * @brief
    * @param     float elapsed
    * @return   void
    */
    virtual void update(float elapsed) = 0;


    /**
    * @fn        render
    * @brief
    * @return   void
    */
    virtual void render() = 0;


    /**
    * @fn        onEnter
    * @brief
    * @return   bool
    */
    virtual bool onEnter() = 0;


    /**
    * @fn        onExit
    * @brief
    * @return   bool
    */
    virtual bool onExit() = 0;


    /**
    * @fn        getStateId
    * @brief
    * @return   std::string
    */
    virtual std::string getStateId() const = 0;


    /**
    * @fn        addChild
    * @brief
    * @return   std::string
    */
    virtual void addChild(GameObject* p) = 0;

};

#endif /* GameState_hpp */
