#ifndef ECS_hpp
#define ECS_hpp
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
  static ComponentID lastID = 0;

  return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
  static ComponentID typeID = getComponentTypeID();

  return typeID;
}

constexpr std::size_t maxComponents = 40;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

/*
 * Holds on component of an entity
 */
class Component {
public:
  Entity *entity;

  virtual void init() {}
  virtual void update() {}
  virtual void draw() {}

  virtual ~Component() {}
};

/*
 * Entity that manages all components of a game object
 */
class Entity {
private:
  bool active = true;
  std::vector<std::unique_ptr<Component>> components;

  ComponentArray componentArray;
  ComponentBitSet componentBitSet;

public:
  /*
   * Updates all components
   */
  void update()
  {
    for (auto &c : components)
      c->update();
    for (auto &c : components)
      c->draw();
  }
  void draw() {}

  /*
   * Returns if component is active
   */
  bool isActive() const { return active; }

  /*
   * Delete component
   */
  void destroy() { active = false; }

  /*
   * Test if component exists
   */
  template <typename T> bool hasComponent() const
  {
    return componentBitSet[getComponentTypeID<T>()];
  }

  /*
   * Adds a component to the entity
   */
  template <typename T, typename... TArgs> T &addComponent(TArgs &&... mArgs)
  {
    T *c(new T(std::forward<TArgs>(mArgs)...));
    c->entity = this;
    std::unique_ptr<Component> uPtr{c};
    components.emplace_back(
        std::move(uPtr)); // Add new component to components

    componentArray[getComponentTypeID<T>()] =
        c; // One type of component should be in the same place for every
           // entity
    componentBitSet[getComponentTypeID<T>()] = true; // Set bit

    c->init();

    return *c;
  }

  template <typename T> T &getComponent() const
  {
    auto ptr(componentArray[getComponentTypeID<T>()]);
    return *static_cast<T *>(ptr);
  }
};

/*
 * Class that manages all Entites
 */
class Manager {
private:
  std::vector<std::unique_ptr<Entity>> entities;

public:
  void update()
  {
    for (auto &e : entities)
      e->update();
  }

  void draw()
  {
    for (auto &e : entities)
      e->draw();
  }

  /*
   * Removes every entity that is not active anymore
   */
  void refresh()
  {
    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                  [](const std::unique_ptr<Entity> &mEntity) {
                                    return !mEntity->isActive();
                                  }),
                   std::end(entities));
  }

  Entity &addEntity()
  {
    Entity *e = new Entity();
    std::unique_ptr<Entity> uPtr{e};
    entities.emplace_back(std::move(uPtr));

    return *e;
  }
};

#endif // ECS
