#ifndef __RENDER_SYSTEM__
#define __RENDER_SYSTEM__

#include <string>
#include "ECS.h"

struct SDL_Window;
struct SDL_Surface;
class SpriteComponent;

class RenderSystem : public System
{
private:
    // Window
    SDL_Window* window;
    std::string windowName;
    uint windowSizeX;
    uint windowSizeY;

    // Screen
    SDL_Surface* screen;
    uint screenXPos;
    uint screenYPos;


public:
    RenderSystem(EntityManager& em, const std::string& windowName, uint xpos, uint ypos, uint xsize, uint ysize);
    ~RenderSystem();

    bool            initWindowAndScreen(const std::string& name, uint xpos, uint ypos, uint xsize, uint ysize);

    void            update() override;
    void            draw(SpriteComponent& c);
};




#endif
