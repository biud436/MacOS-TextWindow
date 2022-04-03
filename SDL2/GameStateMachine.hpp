//
//  GameStateMachine.hpp
//  SDL2
//
//  Created by 어진석 on 2022/04/03.
//

#ifndef GameStateMachine_hpp
#define GameStateMachine_hpp

#include <vector>

class GameState;
using States = std::vector<GameState*>;

/**
 * @class GameStateMachine
 * @brief
 */
class GameStateMachine
{
public:
    GameStateMachine();
    virtual ~GameStateMachine();

    /**
    * @fn        pushState
    * @brief
    * @param     GameState * pNewState
    * @return   void
    */
    void pushState(GameState* pNewState);


    /**
    * @fn        changeState
    * @brief
    * @param     GameState * pNewState
    * @return   void
    */
    void changeState(GameState* pNewState);


    /**
    * @fn        popState
    * @brief
    * @return   void
    */
    void popState();


    /**
    * @fn        update
    * @brief
    * @param     float elapsed
    * @return   void
    */
    void update(float elapsed);


    /**
    * @fn        render
    * @brief
    * @return   void
    */
    void render();

    /**
    * @fn        current
    * @brief
    * @return   GameState*
    */
    GameState* current();


private:

    States m_gameStates;

};

#endif /* GameStateMachine_hpp */
