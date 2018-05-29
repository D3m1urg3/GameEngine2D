#ifndef __GAME__
#define __GAME__

#include <vector>
#include <memory>
#include "Globals.h"
#include "ECS.h"
#include "SDL.h"
#include "InputSystem.h"
#include <windows.h>

#include "RenderSystem.h"

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

    EntityManager emanager;

    // Entities
    Entity* inputListener;

    // Systems
    InputSystem*    inputSystem;
    RenderSystem*   renderSystem;
    std::vector<System*> systems;

    // Variables
    KeyboardKeys currentKey;
public:
    Game();
    ~Game();

    inline const GameStatus& getStatus() const { return status; }
    
    bool init();
    bool destroy();

    void update();
};

#endif

