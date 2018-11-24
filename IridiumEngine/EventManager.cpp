#include "stdafx.h"
#include <assert.h>
#include <windows.h>
#include "Engine/Event/EventManager.h"

EventManager::EventManager()
{
	activeQueueIndex = 0;
}

EventManager* EventManager::Get()
{
	static EventManager* instance = new EventManager();
	return instance;
}

EventManager::~EventManager()
{

}

bool EventManager::AddListener(const EventListenerDelegate& eventDelegate, const EventType& type)
{
	EventListenerList& eventListenerList = eventListeners[type];
	for (auto it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
	{
		if (eventDelegate == (*it))
		{
			throw std::runtime_error("You're attempting to register an event that has already been added. DUPLICATE EVENT");
			return false;
		}
	}

	eventListenerList.push_back(eventDelegate);
	return true;
}

bool EventManager::RemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type)
{
	bool success = false;

	auto findIt = eventListeners.find(type);
	if (findIt != eventListeners.end())
	{
		EventListenerList& listeners = findIt->second;
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			if (eventDelegate == (*it))
			{
				listeners.erase(it);
				success = true;
				break;
			}
		}
	}

	return success;
}

bool EventManager::TriggerEvent(const IEventDataPtr& pEvent) const
{
	bool processed = false;

	auto findIt = eventListeners.find(pEvent->GetEventType());
	if (findIt != eventListeners.end())
	{
		const EventListenerList& eventListenerList = findIt->second;
		for (EventListenerList::const_iterator it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
		{
			EventListenerDelegate listener = (*it);
			listener(pEvent);
			processed = true;
		}
	}

	return processed;
}

bool EventManager::QueueEvent(const IEventDataPtr& pEvent)
{
	assert(activeQueueIndex >= 0);
	assert(activeQueueIndex < EVENTMANAGER_NUM_QUEUES);

	if (!pEvent)
	{
		throw std::runtime_error("Invalid event in QueueEvent()");
		return false;
	}

	auto findIt = eventListeners.find(pEvent->GetEventType());
	if (findIt != eventListeners.end())
	{
		//Sucessfully queuing event
		queues[activeQueueIndex].push_back(pEvent);
		return true;
	}
	else
	{
		//No delegate registered to receive, skipping event
		return false;
	}
}

bool EventManager::AbortEvent(const EventType& type, bool allOfType /*= false*/)
{
	assert(activeQueueIndex >= 0);
	assert(activeQueueIndex < EVENTMANAGER_NUM_QUEUES);

	bool success = false;
	EventListenerMap::iterator findIt = eventListeners.find(type);

	if (findIt != eventListeners.end())
	{
		EventQueue& eventQueue = queues[activeQueueIndex];
		auto it = eventQueue.begin();
		while (it != eventQueue.end())
		{
			auto thisIt = it;
			++it;

			if ((*thisIt)->GetEventType() == type)
			{
				eventQueue.erase(thisIt);
				success = true;
				if (!allOfType)
					break;
			}
		}
	}

	return success;
}

bool EventManager::Update(unsigned long maxMillis /*= INFINITE*/)
{
	unsigned long currMs = GetTickCount();
	unsigned long maxMs = ((maxMillis == IEventManager::kINFINITE) ? IEventManager::kINFINITE : (currMs + maxMillis));

	//swap active queue and clear new queue after swap
	int queueToProcess = activeQueueIndex;
	activeQueueIndex = (activeQueueIndex + 1) % EVENTMANAGER_NUM_QUEUES;
	queues[activeQueueIndex].clear();

	//Process the queue
	while (!queues[queueToProcess].empty())
	{
		//pop the front of the queue
		IEventDataPtr pEvent = queues[queueToProcess].front();
		queues[queueToProcess].pop_front();

		const EventType& eventType = pEvent->GetEventType();

		//find all delegates registered to event
		auto findIt = eventListeners.find(eventType);
		if (findIt != eventListeners.end())
		{
			const EventListenerList& listenerList = findIt->second;

			//call each listener
			for (auto it = listenerList.begin(); it != listenerList.end(); ++it)
			{
				EventListenerDelegate listener = (*it);
				//Sending event
				listener(pEvent);
			}
		}

		//check to see if time ran out
		currMs = GetTickCount();
		if (maxMillis != IEventManager::kINFINITE && currMs >= maxMs)
		{
			//time ran out
			break;
		}

	}

	//if unable to proccess all events, push remaining events to new active queue
	bool queueFlushed = (queues[queueToProcess].empty());
	if (!queueFlushed)
	{
		while (!queues[queueToProcess].empty())
		{
			IEventDataPtr pEvent = queues[queueToProcess].back();
			queues[queueToProcess].pop_back();
			queues[queueToProcess].push_front(pEvent);
		}
	}

	return queueFlushed;
}
