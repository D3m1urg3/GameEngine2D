#ifndef __SPRITE_COMPONENT__
#define __SPRITE_COMPONENT__

#include "ECS.h"
#include "SDL.h"
#include "SDLUtils.h"
#include <string>
#include "Globals.h"

struct Sprite
{
    Texture*        texture     = nullptr;
    SDL_Rect*       src         = nullptr;
    SDL_Rect*       dst         = nullptr;
};

class SpriteComponent : public Component
{
public:
    Sprite* sprite   = nullptr;
};

#endif
