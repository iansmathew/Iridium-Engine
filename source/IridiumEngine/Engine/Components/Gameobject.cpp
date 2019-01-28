#include "Gameobject.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"

/**
	Constructor that sends out the GO_Created event
 */
Gameobject::Gameobject()
{
	std::shared_ptr<EvtDat_On_GO_Created> pEvent(new EvtDat_On_GO_Created(this));
	EventManager::Instance()->QueueEvent(pEvent);
}
