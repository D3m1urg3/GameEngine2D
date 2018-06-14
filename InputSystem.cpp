
#include "Globals.h"
#include "InputSystem.h"

InputSystem::InputSystem(EntityManager& em)
    :System(em)
{
    // Init SDL if it is not already 
    Uint32 sdl_init_mask = SDL_INIT_EVERYTHING;
    Uint32 is_sdl_video_init = sdl_init_mask & SDL_INIT_VIDEO;
    if (!is_sdl_video_init)
    {
        SDL_Init(SDL_INIT_EVERYTHING);
    }
    activate();
}

void InputSystem::update()
{       
    readKeyboardInput();

    // TODO: translate keys to commands from a datafile  

    // Update Entities 
    if (lastKeyDown != NONE_KEY || lastKeyUp != NONE_KEY)
    {
        for (uint id = 0, entityCount = emanager->entityCount(); id < entityCount; ++id)
        {
            if (emanager->isEntityActive(id) && emanager->entityHasComponent<InputComponent>(id))
            {
                InputComponent& inputComponent = emanager->getComponentFromEntity<InputComponent>(id);
                if (lastKeyDown != NONE_KEY)
                {
                    inputComponent.lastKeyDown = lastKeyDown;
                }
                else if (lastKeyUp != NONE_KEY)
                {
                    inputComponent.lastKeyUp = lastKeyUp;
                }
            }
        }
    }
}

void InputSystem::readKeyboardInput()
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        switch (ev.type)
        {
        case SDL_KEYDOWN:
            lastKeyDown = translateKey(ev.key.keysym.sym);
        case SDL_KEYUP:
            lastKeyUp = translateKey(ev.key.keysym.sym);
        }
    }
}

KeyboardKeys& InputSystem::translateKey(const SDL_Keycode& k) const
{
    KeyboardKeys ret = NONE_KEY;
    switch (k)
    {
    case SDLK_ESCAPE:
        ret = ESC_KEY;
        break;
    default:
        ret = NONE_KEY;
        break;
    }

    return ret;
}