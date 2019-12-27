#pragma once
#include "Logger.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
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

	template <typename T>
	bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>];
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
	bool enabled = true;
	std::vector<std::unique_ptr<Component>> components;	

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
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
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isEnabled();
		}),
			std::end(entities));
	}

	Entity& addEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

	size_t GetEntityCount() const {
		return entities.size();
	}

	inline const auto& GetEntities() const {
		return entities;
	}
		
private:
	std::vector<std::unique_ptr<Entity>> entities;
};