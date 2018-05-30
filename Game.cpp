#include "Game.h"

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
    AnimationSystem*    animationSystem = new AnimationSystem(emanager);

    // Push systems in vectors
    // This order determines system update order
    systems.push_back(inputSystem);
    systems.push_back(animationSystem);
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
    AnimationComponent& eanimation  = emanager.addComponentToEntity<AnimationComponent>(e.id);

    etransform.xpos = 0;
    etransform.ypos = 0;

    initEntityAnimation(e.id, "Assets/bomberman_sprites.bmp", 3, 3, 14, 16, 3);
}

void Game::initEntityAnimation(uint entityID, std::string fullfilename, uint init_x, uint init_y, uint xsize, uint ysize, uint framesAmount)
{
    AnimationComponent& animationCmp = emanager.getComponentFromEntity<AnimationComponent>(entityID);

    // Load surface from BMP file
    if (animationCmp.surface != nullptr)
    {
        SDL_FreeSurface(animationCmp.surface);
    }
    SDL_Surface* surface = SDL_LoadBMP(fullfilename.c_str());

    // Init animation sprites
    animationCmp.surface = surface;
    for (uint i = 0; i < framesAmount; ++i)
    {
        Sprite* sprite = new Sprite();
        sprite->src = new SDL_Rect;
        sprite->dst = new SDL_Rect;

        sprite->sdl_surface = surface;
        sprite->src->x = init_x + i*xsize;
        sprite->src->y = init_y;
        sprite->src->w = xsize;
        sprite->src->h = ysize;
        sprite->dst->w = xsize;
        sprite->dst->h = ysize;
        sprite->isInit = true;

        animationCmp.sprites.push_back(sprite);
    }
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
