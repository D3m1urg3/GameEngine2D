#ifndef __ECS__
#define __ECS__

#include <cstddef>
#include <vector>
#include <array>
#include <memory>
#include <bitset>
#include <algorithm>
#include "Globals.h"

// ComponentTypeID Generator

using ComponentTypeID = std::size_t;

inline ComponentTypeID getComponentTypeID()
{
    static ComponentTypeID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentTypeID getComponentTypeID() noexcept
{
    static ComponentTypeID typeID = getComponentTypeID();
    return typeID;
}
// ----------------------------------------------------------------------------------------------------
// Entity & Component base classes

class Component;
class Entity;

constexpr uint          maxEntities     = 100;
constexpr std::size_t   maxComponents   = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
    Component() {}
    virtual ~Component() {}

    Entity* entity;
};

class Entity
{
public:
    uint  id;
    bool active  = false;

    std::vector<std::unique_ptr<Component>> components;
    ComponentArray                          componentArray;
    ComponentBitSet                         componentBitSet;
};

class EntityManager
{
private:
    std::vector <std::unique_ptr<Entity>> entities;

public:
    EntityManager() {}
    ~EntityManager() {}

    // Entity Management
    Entity&                 addEntity       ();
    inline uint             entityCount     ()                      { return entities.size(); }
    inline Entity&          getEntity       (const uint id)         { return *entities.at(id); }
    bool                    isEntityActive  (const uint id);
    void                    disableEntity   (const uint id);
    void                    enableEntity    (const uint id);

    // Component Management
    template <typename T, typename... TArgs> 
    T& addComponentToEntity(const uint entityID, TArgs&&... mArgs)
    {
        // 0. Get Entity
        Entity& e = getEntity(entityID);

        // 1. Create Component
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = &e;
        std::unique_ptr<Component> uPtr{ c };

        // 2. Add Component to entity components
        e.components.emplace_back(std::move(uPtr));
        e.componentArray[getComponentTypeID<T>()] = c;
        e.componentBitSet[getComponentTypeID<T>()] = true;

        return *c;
    }

    template <typename T> 
    T& getComponentFromEntity(const uint entityID) 
    {
        Entity& e = getEntity(entityID);
        auto ptr(e.componentArray[getComponentTypeID<T>()]);

        return *static_cast<T*>(ptr);
    }

    template <typename T> 
    bool entityHasComponent(uint entityID) 
    {
        Entity& e = getEntity(entityID);
        return e.componentBitSet[getComponentTypeID<T>()];
    }
};

class System
{
protected:
    bool            active      = false;
    EntityManager*  emanager    = nullptr;
public:
    System(EntityManager& em);
    virtual ~System() {}

    bool isActive()                       const { return active; }

    void activate()                             { active = true; }
    void deactivate()                           { active = false; }

    virtual void update() {}
};
#endif
// Code inspired in: https://youtu.be/XsvI8Sng6dk