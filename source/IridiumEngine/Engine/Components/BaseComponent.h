#pragma once

/*************************/
/* FORWARD DECLARATIONS  */
/*************************/
class Gameobject;

template <class T>
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
	virtual void Start()
	{
		static_cast<T*>(this)->Start();
	}

	/**
		The update function for the component
	 */
	virtual void Update()
	{
		static_cast<T*>(this)->Update();
	}

	/**
		Shutdown function that takes care of destruction
	 */
	virtual void Shutdown()
	{
		static_cast<T*>(this)->Shutdown();
	}

	/**
		Returns a pointer to the gameobject it belongs to.

		@return Gameobject owner
	 */
	Gameobject* GetGameobject() const
	{
		return owner;
	}

};