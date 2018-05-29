#ifndef __TRANSFORM_COMPONENT__
#define __TRANSFORM_COMPONENT__

#include "ECS.h"
#include "Globals.h"

class TransformComponent : public Component
{
public:
    int xpos;
    int ypos;
};

#endif