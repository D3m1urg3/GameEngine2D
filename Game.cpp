#include "SDL.h"
#include <memory>

#include "Globals.h"
#include "Game.h"

#include "TransformComponent.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "AnimationSystem.h"

Game::Game()
    :status(GAME_INITIALIZING),
    inputListener(nullptr)
{
    if (init())
    {
        status = GAME_RUNNING;
    }
    else
    {
        status = GAME_FINISHED;
    }
}

Game::~Game()
{
    destroy();
}

bool Game::init()
{
    // Create Systems
    InputSystem*        inputSystem     = new InputSystem(emanager); 
    RenderSystem*       renderSystem    = new RenderSystem(emanager, "Game", 100, 100, 300, 300);

    // Push systems in vectors
    // This order determines system update order
    systems.push_back(inputSystem);
    systems.push_back(renderSystem);

    // Run configuration
    configure();

    return true;
}

void Game::configure()
{
    // Create input listener entity. This entity purpose is for the Game to be able to end due to keyboard input
    Entity& listener = emanager.addEntity();
    emanager.addComponentToEntity<InputComponent>(listener.id);
    inputListener = &listener;

    // Test entity
    Entity& e = emanager.addEntity();
    InputComponent&     einput      = emanager.addComponentToEntity<InputComponent>(e.id);
    TransformComponent& etransform  = emanager.addComponentToEntity<TransformComponent>(e.id);
    SpriteComponent&    esprite     = emanager.addComponentToEntity<SpriteComponent>(e.id);

    etransform.xpos = 0;
    etransform.ypos = 0;
}

bool Game::destroy()
{
    for (auto& systemPtr : systems)
    {
        delete systemPtr;
    }

    return true;
}

void Game::update()
{
    if (inputListener != nullptr)
    {
        InputComponent& i = emanager.getComponentFromEntity<InputComponent>(inputListener->id);
        if (ESC_KEY == i.lastKeyDown)
        {
            status = GAME_FINISHED;
        }
    }

    // Update systems
    if(status == GAME_RUNNING)
    {
        for (auto system : systems)
        {
            if (system->isActive())
            { 
                system->update();
            }
        }
    }
}

// Utils
