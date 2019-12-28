#pragma once
#include "Logger.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class EntityManager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
	Entity* entity;

	virtual void OnInit() {}
	virtual void OnUpdate() {}
	virtual void OnDraw() {}
	virtual void OnClear() {}

	virtual ~Component() {}
};

class Entity {
public:
	Entity(EntityManager& mManager) : manager(mManager) {}

	void OnUpdate() {
		for (auto& c : components)
			c->OnUpdate();
	}

	void OnDraw() {
		for (auto& c : components)
			c->OnDraw();
	}

	bool isEnabled() const { return enabled;  }
	void Destroy() { enabled = false; }

	bool hasGroup(Group mGroup)
	{
		return groupBitset[mGroup];
	}

	void AddGroup(Group mGroup);
	void DelGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
	}

	template <typename T>
	bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename...TArgs>
	T& AddComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->OnInit();
		return *c;
	}

	template <typename T>
	T& GetComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

private:
	EntityManager& manager;
	bool enabled = true;
	std::vector<std::unique_ptr<Component>> components;	

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitset groupBitset;
};

class EntityManager {
public:
	void Update() {
		for (auto& e : entities)
			e->OnUpdate();
	}

	void Draw() {
		for (auto& e : entities)
			e->OnDraw();
	}
	
	void Refresh() {
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
				[i](Entity* mEntity)
			{
				return !mEntity->isEnabled() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isEnabled();
		}),
			std::end(entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& AddEntity() {
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

	inline const auto& GetEntities() const {
		return entities;
	}
		
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
};