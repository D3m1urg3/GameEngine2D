#ifndef __GAME__
#define __GAME__

#include <vector>
#include <memory>
#include "Globals.h"
#include "ECS.h"
#include "SDL.h"
#include <windows.h>

#include "TransformComponent.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"

#include "InputSystem.h"
#include "RenderSystem.h"
#include "AnimationSystem.h"

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
    void initEntityAnimation(uint entityID, std::string fullfilename, uint init_x, uint init_y, uint xsize, uint ysize, uint framesAmount);

public:
    Game();
    ~Game();

    inline const GameStatus& getStatus() const { return status; }
    
    bool init();
    bool destroy();

    void update();
};

#endif

