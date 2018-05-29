#ifndef __SPRITE_COMPONENT__
#define __SPRITE_COMPONENT__

#include "ECS.h"
#include "SDL.h"
#include <string>
#include "Globals.h"

class SpriteComponent : public Component
{
public:
    bool isLoaded = false;
    SDL_Surface*    sdl_surface = nullptr;
    SDL_Rect*       src         = nullptr;
    SDL_Rect*       dst         = nullptr;
};

#endif
