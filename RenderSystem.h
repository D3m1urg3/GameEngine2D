#ifndef __RENDER_SYSTEM__
#define __RENDER_SYSTEM__

#include "ECS.h"
#include "SDL.h"
#include <string>
#include "Globals.h"

#include "SpriteComponent.h"

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
    RenderSystem(EntityManager& em);
    ~RenderSystem();

    bool            initWindowAndScreen(const std::string name, uint xpos, uint ypos, uint xsize, uint ysize);

    void            update() override;
    void            draw(SpriteComponent& c);

    SDL_Surface*    loadSDLSurfaceFromBMPFile(std::string str);
    void            freeSDLSurface(SDL_Surface* surface);
};




#endif
