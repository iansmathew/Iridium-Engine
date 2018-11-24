#pragma once
#include "IEventManager.h"

class EvtData_On_Key_Event : public BaseEventData
{
private:
	int key;

public:
	static const EventType eventType;

	EvtData_On_Key_Event()
	{
		key = -1;
	}

	explicit EvtData_On_Key_Event(int _key)
	{
		key = _key;
	}

	virtual const EventType& GetEventType() const override
	{
		return eventType;
	}

	unsigned int GetKeyValue()
	{
		return key;
	}
};