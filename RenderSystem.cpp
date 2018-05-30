#include "RenderSystem.h"

RenderSystem::RenderSystem(EntityManager& em, std::string windowName, uint xpos, uint ypos, uint xsize, uint ysize)
    :System(em),
    window(nullptr),
    screen(nullptr)
{
    Uint32 sdl_init_mask = SDL_INIT_EVERYTHING;
    bool is_sdl_video_init = sdl_init_mask & SDL_INIT_VIDEO;
    if (!is_sdl_video_init)
    {
        SDL_Init(SDL_INIT_EVERYTHING);
    }
    activate();
    initWindowAndScreen(windowName, xpos, ypos, xsize, ysize);
}

RenderSystem::~RenderSystem()
{
    freeSDLSurface(screen);
    SDL_DestroyWindow(window);
    SDL_Quit;
}

bool RenderSystem::initWindowAndScreen(const std::string name, uint xpos, uint ypos, uint xsize, uint ysize)
{
    window = SDL_CreateWindow(name.c_str(), xpos, ypos, xsize, ysize, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
    return window != nullptr && screen != nullptr;
}

void RenderSystem::freeSDLSurface(SDL_Surface* surface)
{
    if (surface != nullptr)
    {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
}

void RenderSystem::draw(SpriteComponent& c)
{
    if (c.sprite != nullptr)
    {
        SDL_BlitSurface(c.sprite->sdl_surface, c.sprite->src, screen, c.sprite->dst);
        SDL_UpdateWindowSurface(window);
    }
}

void RenderSystem::update()
{
    for (uint id = 0, entityCount = emanager->entityCount(); id < entityCount; ++id)
    {
        if (emanager->isEntityActive(id) && emanager->entityHasComponent<SpriteComponent>(id))
        {
            draw(emanager->getComponentFromEntity<SpriteComponent>(id));
        }
    }
}