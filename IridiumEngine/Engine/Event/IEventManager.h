#pragma once

#include <memory>
#include <concurrent_queue.h>
#include "../../ExternalTools/FastDelegate.h"

//---------------------------------------
// Forward Declarations & typedefs
//---------------------------------------
class IEventData;

typedef unsigned long EventType;
typedef std::shared_ptr<IEventData> IEventDataPtr;
typedef fastdelegate::FastDelegate1<IEventDataPtr> EventListenerDelegate;
typedef concurrency::concurrent_queue<IEventDataPtr> ThreadSafeEventQueue;

class IEventData
{
public:
	virtual ~IEventData() {}
	virtual const EventType& GetEventType() const = 0;
	virtual float GetTimeStamp() const = 0;

};

class BaseEventData : public IEventData
{
private:
	const float timeStamp;
	static const EventType eventType;

public:
	explicit BaseEventData(const float _timeStamp = 0.0f) : timeStamp(_timeStamp) {}
	virtual const EventType& GetEventType(void) const = 0;
	virtual float GetTimeStamp() const override { return timeStamp; }

};

class IEventManager
{
public:
	enum EConstants { kINFINITE = 0xffffffff };
	explicit IEventManager() {}
	~IEventManager() {}

	virtual bool AddListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;
	virtual bool RemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;
	virtual bool TriggerEvent(const IEventDataPtr& pEvent) const = 0;
	virtual bool QueueEvent(const IEventDataPtr& pEvent) = 0;
	virtual bool AbortEvent(const EventType& type, bool allOfType = false) = 0;
	virtual bool Update(unsigned long maxMillis = kINFINITE) = 0;

};