#ifndef __SDL_UTILS__
#define __SDL_UTILS__

#include "SDL.h"
#include <string>

// Texture wrapper class
class Texture
{
private:
    SDL_Surface* surface;
public:
    Texture();
    ~Texture();

    inline bool isLoaded() const { return surface != nullptr; }
    inline SDL_Surface* getSDLSurface() { return surface; }

    bool load(std::string fullfilename);
    
};


#endif
