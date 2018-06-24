#include "SDL.h"
#include "Globals.h"
#include "RenderSystem.h"
#include "SpriteComponent.h"
#include "SDLUtils.h"

RenderSystem::RenderSystem(EntityManager& em, const std::string& windowName, uint xpos, uint ypos, uint xsize, uint ysize)
    :System(em),
    window(nullptr),
    screen(nullptr),
    windowSizeX(xsize),
    windowSizeY(ysize),
    screenXPos(xpos),
    screenYPos(ypos),
    ok(false)
{
}

bool RenderSystem::init()
{
    end();

    ok = initSDLVideo() && initWindowAndScreen(windowName, screenXPos, screenYPos, windowSizeX, windowSizeY);
    activate();

    if (!ok)
    {
        end();
    }
    return ok;
}

void RenderSystem::end()
{
    if (ok)
    {
        SDL_FreeSurface(screen);
        SDL_DestroyWindow(window);
        SDL_Quit();
        ok = false;
    }
}

RenderSystem::~RenderSystem()
{
    end();
}

bool RenderSystem::initWindowAndScreen(const std::string& name, uint xpos, uint ypos, uint xsize, uint ysize)
{
    window = SDL_CreateWindow(name.c_str(), xpos, ypos, xsize, ysize, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
    return window != nullptr && screen != nullptr;
}

void RenderSystem::draw(SpriteComponent& c)
{
    if (c.sprite != nullptr && c.sprite->texture->isLoaded())
    {
        SDL_BlitSurface(c.sprite->texture->getSDLSurface(), c.sprite->src, screen, c.sprite->dst);
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