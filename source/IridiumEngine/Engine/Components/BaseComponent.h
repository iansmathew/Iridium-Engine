#pragma once

/*************************/
/* FORWARD DECLARATIONS  */
/*************************/
class Gameobject;

//class BaseComponentNonTemplated
//{
//public:
//	BaseComponentNonTemplated() {}
//	~BaseComponentNonTemplated() {}
//
//	virtual void Start() = 0;
//	virtual void Update() = 0;
//	virtual void Shutdown() = 0;
//};

class BaseComponent 
{
protected:
	bool isUpdated;

private:
	Gameobject* owner;

public:

	/**
		Constructor that takes in the owned gameobject.
	 */
	BaseComponent(Gameobject* _owner)
	{
		isUpdated = true;
		owner = _owner;
	}

	/**
		Called before any updates are run.
		Use this to set up the component
	 */
	virtual void Start() = 0;

	/**
		The update function for the component
	 */
	virtual void Update() = 0;

	/**
		Shutdown function that takes care of destruction
	 */
	virtual void Shutdown() = 0;

	/**
		Returns a pointer to the gameobject it belongs to.

		@return Gameobject owner
	 */
	Gameobject* GetGameobject() const
	{
		return owner;
	}

};