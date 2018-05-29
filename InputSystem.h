#ifndef __INPUT_SYSTEM__
#define __INPUT_SYSTEM__

#include "ECS.h"
#include "SDL.h"
#include "Globals.h"

#include "InputComponent.h"

class InputSystem : public System
{
private:
    KeyboardKeys lastKeyDown;
    KeyboardKeys lastKeyUp;

    void readKeyboardInput();
    const KeyboardKeys& translateKey(SDL_Keycode k);
public:
    InputSystem(EntityManager& em);
    ~InputSystem() {}

    void update();
};




#endif
