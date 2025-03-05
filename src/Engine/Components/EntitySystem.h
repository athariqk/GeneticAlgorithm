#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <memory>
#include <vector>

/* Source: https://github.com/carlbirch/BirchEngine */

class Component;
class Entity;
class EntityManager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() {
    static ComponentID lastID = 0u;
    return lastID++;
}

template<typename T>
inline ComponentID getComponentTypeID() noexcept {
    static_assert(std::is_base_of_v<Component, T>, "");
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;
using ComponentArray = std::array<Component *, maxComponents>;

class Component {
public:
    Entity *entity;

    virtual void OnInit() {}

    virtual void OnUpdate(float delta) {}

    virtual void OnDraw() {}

    virtual void OnEvent() {}

    virtual void OnClear() {}

    virtual ~Component() {}
};

class Entity {
public:
    Entity(EntityManager &mManager) : manager(mManager) {}

    void OnUpdate(float delta) {
        for (auto &c: components)
            c->OnUpdate(delta);
    }

    void OnDraw() {
        for (auto &c: components)
            c->OnDraw();
    }

    void OnEvent() {
        for (auto &c: components)
            c->OnEvent();
    }

    void OnClear() {
        for (auto &c: components)
            c->OnClear();
    }

    bool isEnabled() const { return enabled; }
    void Destroy() { enabled = false; }

    bool hasGroup(Group mGroup) { return groupBitset[mGroup]; }

    void AddGroup(Group mGroup);

    void DelGroup(Group mGroup) { groupBitset[mGroup] = false; }

    template<typename T>
    bool hasComponent() const {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template<typename T, typename... TArgs>
    T &AddComponent(TArgs &&...mArgs) {
        T *c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->OnInit();
        return *c;
    }

    template<typename T>
    T &GetComponent() const {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T *>(ptr);
    }

private:
    EntityManager &manager;
    bool enabled = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitset groupBitset;
};

class EntityManager {
public:
    void Update(float delta) {
        for (auto &e: entities)
            e->OnUpdate(delta);
    }

    void Draw() {
        for (auto &e: entities)
            e->OnDraw();
    }

    void Event() {
        for (auto &e: entities)
            e->OnEvent();
    }

    void Clear() {
        for (auto &e: entities)
            e->OnClear();
    }

    void Refresh() {
        for (auto i(0u); i < maxGroups; i++) {
            auto &v(groupedEntities[i]);
            std::erase_if(v, [i](Entity *mEntity) { return !mEntity->isEnabled() || !mEntity->hasGroup(i); });
        }

        std::erase_if(entities, [](const std::unique_ptr<Entity> &mEntity) { return !mEntity->isEnabled(); });
    }

    void AddToGroup(Entity *mEntity, Group mGroup) { groupedEntities[mGroup].emplace_back(mEntity); }

    std::vector<Entity *> &GetGroup(Group mGroup) { return groupedEntities[mGroup]; }

    Entity &AddEntity() {
        auto e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }

    inline const auto &GetEntities() const { return entities; }

private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity *>, maxGroups> groupedEntities;
};
