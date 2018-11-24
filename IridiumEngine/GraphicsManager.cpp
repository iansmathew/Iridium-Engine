#include "stdafx.h"
#include "Engine/Graphics/GraphicsManager.h"
#include "Engine/Event/EventManager.h"
#include "Engine/Event/Events.h"

GraphicsManager::GraphicsManager()
{
	
}

GraphicsManager::~GraphicsManager()
{

}

bool GraphicsManager::Initialize(int screenWidth, int screenHeight, HWND HWnd)
{
	//TODO: Remove unwanted event queuing

	//EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate(this, &GraphicsManager::HandleEvent);
	//EventManager::Get()->AddListener(delegateFunc, EvtData_On_Key_Event::eventType);

	return true;
}

bool GraphicsManager::Frame()
{
	return true;
}

void GraphicsManager::Shutdown()
{
	
}
#include <string.h>

void GraphicsManager::HandleEvent(IEventDataPtr pEventData)
{
	//TODO: Remove unwanted event queuing

	//std::shared_ptr<EvtData_On_Key_Event> pCastEventData = std::static_pointer_cast<EvtData_On_Key_Event>(pEventData);

	//char* x = new char(pCastEventData->GetKeyValue());
	//OutputDebugStringA(x);
}
