#ifndef __INPUT_COMPONENT__
#define __INPUT_COMPONENT__

#include "ECS.h"

enum KeyboardKeys
{
    NONE_KEY,
    ESC_KEY,
    UP_KEY,
    DOWN_KEY,
    LEFT_KEY,
    RIGHT_KEY
};


class InputComponent : public Component
{
public:
    KeyboardKeys lastKeyDown;
    KeyboardKeys lastKeyUp;
};

#endif
