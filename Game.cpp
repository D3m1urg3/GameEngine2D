#include "Game.h"

Game::Game()
    :status(GAME_INITIALIZING),
    inputListener(nullptr),
    inputSystem(nullptr),
    renderSystem(nullptr)
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
    inputSystem     = new InputSystem(emanager); 
    renderSystem    = new RenderSystem(emanager);

    // Init Systems
    renderSystem->initWindowAndScreen("test", 100, 100, 100, 100);

    // Push systems in vectors
    // This order determines system update order
    systems.push_back(inputSystem);
    systems.push_back(renderSystem);

    // Create input listener entity. This entity purpose is for the Game to be able to end due to keyboard input
    Entity& e = emanager.addEntity();
    emanager.addComponentToEntity<InputComponent>(e.id);
    inputListener = &e;

    return true;
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
