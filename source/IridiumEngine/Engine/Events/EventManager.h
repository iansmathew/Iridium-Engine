#pragma once
#include "IEventManager.h"
#include "../../Helper/BaseSingleton.h"
#include <list>
#include <map>

const unsigned int EVENTMANAGER_NUM_QUEUES = 2;

class EventManager : public IEventManager, public BaseSingleton<EventManager>
{
private:
	typedef std::list<EventListenerDelegate> EventListenerList;
	typedef std::map<EventType, EventListenerList> EventListenerMap;
	typedef std::list<IEventDataPtr> EventQueue;

	EventListenerMap eventListeners;
	EventQueue queues[EVENTMANAGER_NUM_QUEUES];
	int activeQueueIndex;

private:
	friend BaseSingleton;
	explicit EventManager();

public:
	~EventManager();

	virtual bool AddListener(const EventListenerDelegate& eventDelegate, const EventType& type) override;


	virtual bool RemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) override;


	virtual bool TriggerEvent(const IEventDataPtr& pEvent) const override;


	virtual bool QueueEvent(const IEventDataPtr& pEvent) override;


	virtual bool AbortEvent(const EventType& type, bool allOfType = false) override;


	virtual bool Update(unsigned long maxMillis = kINFINITE) override;


};