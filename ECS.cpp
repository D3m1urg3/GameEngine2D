#include "ECS.h"

// Entity Manager

Entity& EntityManager::addEntity()
{
    Entity* e = new Entity();
    e->id     = entities.size(); // id corresponds to index in entities vector
    std::unique_ptr<Entity> uPtr{ e };
    entities.emplace_back(std::move(uPtr));
    return *e;
}

bool EntityManager::isEntityActive(const uint id)
{
    Entity& e = getEntity(id); 
    return e.active;
}

void EntityManager::disableEntity(const uint id)
{
    Entity& e = getEntity(id); 
    e.active = false;
}

void EntityManager::enableEntity(const uint id)
{
    Entity& e = getEntity(id); 
    e.active = true;
}

// System
System::System(EntityManager& em)
    :active(true),
    emanager(&em)
{}