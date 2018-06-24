#ifndef __INPUT_SYSTEM__
#define __INPUT_SYSTEM__

#include "SDL.h"
#include "ECS.h"
#include "InputComponent.h"

class EntityManager;

class InputSystem : public System
{
private:
    bool ok;

    KeyboardKeys lastKeyDown;
    KeyboardKeys lastKeyUp;

    void readKeyboardInput();
    KeyboardKeys& translateKey(const SDL_Keycode& k) const;
public:
    InputSystem(EntityManager& em);
    ~InputSystem();

    bool init() override;
    void end() override;

    void update() override;
};




#endif
