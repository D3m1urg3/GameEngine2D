#include <string>
#include <map>
#include "SDL.h"
#include "Globals.h"
#include "SDLUtils.h"

Texture::Texture()
    :surface(nullptr)
{}

Texture::Texture(const std::string& fullfilename)
    :surface(nullptr)
{
    surface = SDL_LoadBMP(fullfilename.c_str());
}

Texture::~Texture()
{
    if (surface.isUnique())
    {
        SDL_FreeSurface(surface.get());
    }
}

bool Texture::load(const std::string& fullfilename)
{
    surface = SDL_LoadBMP(fullfilename.c_str());
    return surface.get() != nullptr;
}