#ifndef __ECS__
#define __ECS__
#include <array>
#include <cassert>
#include "Globals.h"

// Constants and typedefs
constexpr uint MAX_NUM_ENTITIES   = 100; // Arbitrary
constexpr uint MAX_NUM_COMPONENTS = 65536; // 2^16 components

typedef std::size_t EntityID;
typedef std::size_t ComponentID;
typedef uint16_t Bitmask;
// ---------------------------------------------------------------------------------------------
// ID Utils

inline std::size_t generateComponentID()
{
    static std::size_t last = 0;
    return last++;
}

template <typename T> inline std::size_t getComponentID()
{
    static std::size_t componentID = generateComponentID();
    return componentID;
}
// ---------------------------------------------------------------------------------------------

std::array<Bitmask, MAX_NUM_ENTITIES> entity_masks;
std::array<Component*, MAX_NUM_COMPONENTS> components;

class Component
{
public:
    const EntityID entityID;
    virtual ~Component();
};

class System
{
private:

public:
    virtual void init() {}
    virtual void update() {}
    
    virtual ~System() {}
};


#endif
