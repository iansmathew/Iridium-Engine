#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <bitset>
#include <memory>
#include <array>

#include "BaseComponent.h"
#include "TrialComponent.h"
#include "TransformComponent.h"
#include <assert.h>
#include "MusicComponent.h"

class SceneManager;

constexpr std::size_t  maxComponents = 32;

using ComponentsExistBitset = std::bitset<maxComponents>;
using ComponentPointerArray = std::vector<BaseComponent*>;


//Temp
class TransformComponent;
class RenderComponent;




/// <summary>
/// Gameobject Class
/// </summary>
class Gameobject
{
private:

	/// <summary>
	/// Is Gameobject active.
	/// </summary>
	bool isActive = true;

	unsigned int instanceID;

	// Scene Hierarchy
	Gameobject* parent;
	std::vector<Gameobject*> children;


	//Component System
	//std::vector<std::unique_ptr<BaseComponent>> components;

	ComponentsExistBitset componentExists;
	ComponentPointerArray componentArray;
	
protected:

	/* The constructor is protected so that an instance of GO cannot be created
	unless through the Scene Manager or through derived classes*/
	friend SceneManager;
	Gameobject(bool _isRendered = true);

public:
	/// <summary>
	/// Game Object Name
	/// </summary>
	std::string name = "Gameobject";

	std::string GetName() {
		return name;
	}

	void SetName(std::string name) {
		this->name = name;
	}
	

public:
	~Gameobject();

#pragma region GAME_FLOW_FUNCS

	virtual void Start();

	virtual void Update(float _deltaTime);

	virtual void Draw(sf::RenderTarget& _windowRef, sf::RenderStates _states);

	virtual void Shutdown();

#pragma endregion GAME_FLOW_FUNCS
	
#pragma region GETTERS

	/* Returns the unique instance ID of the gameobject */
	inline int GetInstanceID() const { return instanceID; }


	inline bool IsActive() const { return isActive; }

	template<typename T>
	bool HasComponent() const { return componentExists[GetComponentTypeID<T>()];}

	TransformComponent* GetTransform() {
		return GetComponent<TransformComponent>();
	}


	/* Returns the parents of the gameobject */
	inline Gameobject* GetParent() const { return parent; }


#pragma endregion GETTERS

#pragma region GAMEOBJECT_FUNCS

	void AddChild(Gameobject* _child);

	bool RemoveChild(Gameobject* _child);

	template <class T, typename... TArgs, class = typename std::enable_if<std::is_base_of<BaseComponent,T>::value,void*>::type>
	T* AddComponent(TArgs&&... mArgs)
	{
		T* c = (new T(std::forward<TArgs>(mArgs)...));

		//std::unique_ptr<BaseComponent> uPtr{ c };

		//components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentExists[GetComponentTypeID<T>()] = true;

		c->Start();

		return c;
	}


	template <class T>
	T* GetComponent() const
	{

		assert(HasComponent<T>() && "Does not have component.");
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return dynamic_cast<T*>(ptr);

	}

	MusicComponent* GetMusicComponent() {
		assert(HasComponent<MusicComponent>() && "Does not have component.");
		auto ptr(componentArray[GetComponentTypeID<MusicComponent>()]);
		return dynamic_cast<MusicComponent*>(ptr);
	}


	virtual void SerializeData(std::string _jsonString);

#pragma endregion GAMEOBJECT_FUNCS
};


