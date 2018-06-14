#include "SDLUtils.h"

Texture::Texture()
    :surface(nullptr)
{}

Texture::~Texture()
{
    SDL_FreeSurface(surface);
    surface = nullptr;
}

bool Texture::load(std::string fullfilename)
{
    surface = SDL_LoadBMP(fullfilename.c_str());
    return surface != nullptr;
}