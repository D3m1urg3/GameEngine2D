#ifndef __GAME__
#define __GAME__

#include <vector>
#include "ECS.h"

#include "InputComponent.h"


enum GameStatus
{
    GAME_INITIALIZING,
    GAME_RUNNING,
    GAME_FINISHED
};

class Game
{
private:
    GameStatus status;

    // Entities
    EntityManager emanager;
    Entity* inputListener;

    // Systems
    std::vector<System*> systems;

    // Others
    KeyboardKeys currentKey;

    // ------------------------------------
    // Configuration and utility functions
    void configure();
public:
    Game();
    ~Game();

    inline const GameStatus& getStatus() const { return status; }
    
    bool init();
    bool destroy();

    void update();
};

#endif

