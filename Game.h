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
    bool ok;
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
    bool init();
    void end();

    inline bool isOk() const { return ok; }

    inline const GameStatus& getStatus() const { return status; }

    void update();
};

#endif

