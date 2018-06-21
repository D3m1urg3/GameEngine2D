#ifndef __SPRITE_COMPONENT__
#define __SPRITE_COMPONENT__

#include "ECS.h"
class Texture;
struct SDL_Rect;

struct Sprite
{
    Texture*        texture     = nullptr;
    SDL_Rect*       src         = nullptr;
    SDL_Rect*       dst         = nullptr;
};

class SpriteComponent : public Component
{
public:
    Sprite* sprite;
};

#endif
