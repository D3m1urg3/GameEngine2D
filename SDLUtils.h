#ifndef __SDL_UTILS__
#define __SDL_UTILS__

template <class T> 
class SharedPtr;

// Texture wrapper class
class Texture
{
public:
    Texture();
    Texture(const std::string& fullfilename);
    ~Texture();

    inline bool isLoaded() const { return surface.get() != nullptr; }
    inline SDL_Surface* getSDLSurface() { return surface.get(); }

    bool load(const std::string& fullfilename);
private:
    SharedPtr<SDL_Surface> surface;
};
#endif
