#include "RenderSystem.h"

RenderSystem::RenderSystem(EntityManager& em)
    :System(em),
    window(nullptr),
    screen(nullptr)
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        activate();
    }
}

RenderSystem::~RenderSystem()
{
    deactivate();
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

SDL_Surface* RenderSystem::loadSDLSurfaceFromBMPFile(std::string str)
{
    return SDL_LoadBMP(str.c_str());
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
    SDL_BlitSurface(c.sdl_surface, c.src, screen, c.dst);
    SDL_UpdateWindowSurface(window);
}

void RenderSystem::update()
{
    uint entityCount = emanager->entityCount();
    for (uint id = 0; id < entityCount; ++id)
    {
        if (emanager->isEntityActive(id) && emanager->entityHasComponent<SpriteComponent>(id))
        {
            draw(emanager->getComponentFromEntity<SpriteComponent>(id));
        }
    }
}