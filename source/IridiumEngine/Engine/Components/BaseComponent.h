#pragma once

/*************************/
/* FORWARD DECLARATIONS  */
/*************************/
class Gameobject;

using ComponentID = size_t;

inline ComponentID GetComponentTypeID() {
	static ComponentID previousID = 0;
	return previousID++;
}


/// <summary>
/// Gets the ComponentsID
/// </summary>
/// <returns>Component ID</returns>
template <typename T>
inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID TypeId = GetComponentTypeID();
	return TypeId;
}

/// <summary>
/// Base Class of all Components
/// </summary>
class BaseComponent
{
protected:
	/// <summary>
	/// does component update
	/// </summary>
	bool isUpdated;

private:
	Gameobject* owner;

public:

	 /// <summary>
	 /// Initializes a new instance of the <see cref="BaseComponent"/> class.
	 /// </summary>
	 /// <param name="_owner">The owning gameobject.</param>
	BaseComponent(Gameobject* _owner)
	{
		isUpdated = true;
		owner = _owner;
	}

	~BaseComponent() = default;

	 /// <summary>
	 /// Called before any updates are run.
	 /// Use this to set up the component
	 /// </summary>
	virtual void Start() = 0;

	/// <summary>
	/// The update function for the component
	/// </summary>
	virtual void Update() = 0;


	/// <summary>
	/// Shutdown function that takes care of destruction
	/// </summary>
	virtual void Shutdown() = 0;


	/// <summary>
	/// Returns a pointer to the gameobject it belongs to.
	/// </summary>
	/// <returns>Gameobject owner</returns>
	Gameobject* GetGameobject() const
	{
		return owner;
	}

	//bool operator!=(const BaseComponent& rhs) {
	//	return this != nullptr;
	//}

};