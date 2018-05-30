#ifndef __SPRITE_COMPONENT__
#define __SPRITE_COMPONENT__

#include "ECS.h"
#include "SDL.h"
#include <string>
#include "Globals.h"

struct Sprite
{
    bool            isInit      = false;
    SDL_Surface*    sdl_surface = nullptr;
    SDL_Rect*       src         = nullptr;
    SDL_Rect*       dst         = nullptr;
};

class SpriteComponent : public Component
{
public:
    bool    isLoaded = false;
    Sprite* sprite   = nullptr;
};

#endif
