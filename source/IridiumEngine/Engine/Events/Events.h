#pragma once
#include "IEventManager.h"

//FORWARD DECLARATION
class Gameobject;

class EvtData_On_GO_Created : public BaseEventData
{
private:
	Gameobject* gameobject;

public:
	/**
		Constructor that takes in a gameobject ref to create the event arg

		@param _gameobject: Gameobject reference
	*/
	EvtData_On_GO_Created(Gameobject* _gameobjectRef)
	{
		gameobject = _gameobjectRef;
	}

	static const EventType eventType;

	virtual const EventType& GetEventType(void) const override
	{
		return eventType;
	}

	Gameobject* GetOwnedGameobject()
	{
		return gameobject;
	}
};

class EvtData_On_Scene_Change : public BaseEventData
{
public:
	EvtData_On_Scene_Change()
	{

	}

	static const EventType eventType;

	virtual const EventType& GetEventType(void) const override
	{
		return eventType;
	}
};

//Foward declaration inside the SFML namespace
namespace sf
{
	class Sound;
	class Music;
}
class EvtData_On_Request_Play_Sound : public BaseEventData
{
private:
	sf::Sound* soundClip;

public:
	EvtData_On_Request_Play_Sound(sf::Sound* _soundToPlay)
	{
		soundClip = _soundToPlay; //set pointer to clip
	}

	static const EventType eventType;

	virtual const EventType& GetEventType(void) const override
	{
		return eventType;
	}

	sf::Sound* GetSound()
	{
		return soundClip;
	}
};

class EvtData_On_Request_Stream_Music : public BaseEventData
{
private:
	sf::Music* musicClip;

public:
	EvtData_On_Request_Stream_Music(sf::Music* _musicToPlay)
	{
		musicClip = _musicToPlay;
	}

	static const EventType eventType;

	virtual const EventType& GetEventType(void) const override
	{
		return eventType;
	}

	sf::Music* GetMusic() { return musicClip; }

};

class RigidbodyComponent;

class EvtData_On_Rigidbody_Created : public BaseEventData
{
public:
	EvtData_On_Rigidbody_Created(RigidbodyComponent* _rb)
	{
		rb = _rb;
	}
	
	RigidbodyComponent* rb;

	static const EventType eventType;

	virtual const EventType& GetEventType(void) const override
	{
		return eventType;
	}
};

class EvtData_Pre_Scene_Load : public BaseEventData
{
public:
	static const EventType eventType;

	virtual const EventType& GetEventType(void) const override
	{
		return eventType;
	}
};