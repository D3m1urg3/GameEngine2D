#include "SDLUtils.h"

// Utils
bool initSDLVideo()
{
    bool ret = true;
    Uint32 is_sdl_video_init = SDL_INIT_EVERYTHING & SDL_INIT_VIDEO;
    if (!is_sdl_video_init)
    {
        ret = (SDL_Init(SDL_INIT_EVERYTHING) == 0);
    }
    return ret;
}

// Texture Wrapper
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
    else
    {
        surface.free();
    }
}

bool Texture::load(const std::string& fullfilename)
{
    surface = SDL_LoadBMP(fullfilename.c_str());
    return surface.get() != nullptr;
}

// Texture Manager
TextureManager::TextureManager()
    :ok(false)
{}

TextureManager::~TextureManager()
{
    end();
}

bool TextureManager::init()
{
    end();
    ok = true;

    //...

    if (!ok)
    {
        end();
    }
    return ok;
}

void TextureManager::end()
{
    if (ok)
    {
        for (auto& e : textures)
        {
            DELETE(e.second);
            textures.erase(e.first);
        }
        ok = false;
    }

}

Texture* TextureManager::load(const std::string& id, const std::string& fullfilename)
{
    Texture* ret = nullptr;
    if (!isManaged(id))
    {
        ret = new Texture(fullfilename);
        textures[id] = ret;
    }

    return ret;
}

Texture* TextureManager::getTexture(const std::string& id)
{
    Texture* ret = nullptr;
    std::map<std::string, Texture*>::iterator it = textures.find(id);
    if (it != textures.end())
    {
        ret = it->second;
    }

    return ret;
}