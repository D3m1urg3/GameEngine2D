#ifndef __SDL_UTILS__
#define __SDL_UTILS__

#include <string>
#include <map>
#include "SDL.h"
#include "Globals.h"

// Texture wrapper class
class Texture
{
public:
    Texture();
    Texture(const std::string& fullfilename);
    ~Texture();

    bool load(const std::string& fullfilename);

    bool isLoaded() const { return !surface.isNull(); }
    SDL_Surface* getSDLSurface() { return surface.get(); }
private:
    SharedPtr<SDL_Surface> surface;
};

// Texture Manager
class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    bool init();
    void end();

    bool isManaged(const std::string& id) { return textures.find(id) != textures.end(); }

    Texture* load(const std::string& id, const std::string& fullfilename);
    Texture* getTexture(const std::string& id);
private:
    bool ok;
    std::map<std::string, Texture*> textures;
};

// Utils
bool initSDLVideo();

#endif
