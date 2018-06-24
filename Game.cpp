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

#include "SDLUtils.h"

Game::Game()
    :status(GAME_INITIALIZING),
    inputListener(nullptr),
    ok(false)
{
}

Game::~Game()
{
    end();
}

bool Game::init()
{
    end();
    ok = true;

    // Create Systems
    InputSystem*        inputSystem     = new InputSystem(emanager); 
    RenderSystem*       renderSystem    = new RenderSystem(emanager, "Game", 100, 100, 300, 300);

    // Push systems in vectors
    // This order determines system update order
    systems.push_back(inputSystem);
    systems.push_back(renderSystem);

    // Create input listener entity. This entity purpose is for the Game to be able to end due to keyboard input
    Entity& listener = emanager.addEntity();
    emanager.addComponentToEntity<InputComponent>(listener.id);
    inputListener = &listener;

    // Configuration
    configure();

    status = GameStatus::GAME_RUNNING;

    if (!ok)
    {
        end();
    }
    return ok;
}

void Game::end()
{
    if (ok)
    {
        for (auto& systemPtr : systems)
        {
            DELETE(systemPtr);
        }
        ok = false;
    }
}

void Game::configure()
{
    // Test entity
    Entity& e = emanager.addEntity();
    InputComponent&     einput      = emanager.addComponentToEntity<InputComponent>(e.id);
    TransformComponent& etransform  = emanager.addComponentToEntity<TransformComponent>(e.id);
    SpriteComponent&    esprite     = emanager.addComponentToEntity<SpriteComponent>(e.id);

    etransform.xpos = 0;
    etransform.ypos = 0;
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