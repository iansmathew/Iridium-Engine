#include "stdafx.h"
#include "Engine/Graphics/GraphicsManager.h"
#include "Engine/Event/EventManager.h"
#include "Engine/Event/Events.h"

GraphicsManager::GraphicsManager()
{
	D3DSys = nullptr;

	//Defining clear color
	bgRGBA[0] = 0.5f;
	bgRGBA[1] = 0.5f;
	bgRGBA[2] = 0.5f;
	bgRGBA[3] = 1.0f;

}

GraphicsManager::~GraphicsManager()
{

}

bool GraphicsManager::Initialize(int screenWidth, int screenHeight, HWND HWnd)
{
	//TODO: Remove unwanted event queuing
	//Subscribe to mouse events
	EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate(this, &GraphicsManager::HandleEvent);
	EventManager::Get()->AddListener(delegateFunc, EvtData_On_Mouse_Event::eventType);

	/**********************************
				DIRECT 3D
	**********************************/

	D3DSys = std::shared_ptr<D3DSystem>(new D3DSystem());
	if (!D3DSys)
	{
		return false;
	}

	//Initialize Direct3D system
	bool result = D3DSys->Initialize(screenWidth, screenHeight, IS_VSYNC_ENABLED, HWnd, IS_FULLSCREEN_ENABLED, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
		MessageBox(HWnd, L"Could not initialize Direct3D", L"Error", MB_OK);



	return true;
}

bool GraphicsManager::Frame()
{
	bool result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsManager::Render()
{
	//Clear buffer
	D3DSys->BeginScene(bgRGBA[0], bgRGBA[1], bgRGBA[2], bgRGBA[3]); //Gray

	//Present rendered  scene to screen
	D3DSys->EndScene();

	return true;
}

void GraphicsManager::Shutdown()
{
	//Removing objects from last added to first

	if (D3DSys)
	{
		D3DSys->Shutdown();
	}
}
#include <string.h>

void GraphicsManager::HandleEvent(IEventDataPtr pEventData)
{
	//TODO: Remove unwanted event queuing
	//Cast generic event to required type
	std::shared_ptr<EvtData_On_Mouse_Event> pCastEventData = std::static_pointer_cast<EvtData_On_Mouse_Event>(pEventData);
	
	// Set random background color
	for (int i = 0; i < 3; i++) //alpha is const
	{
		bgRGBA[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}
}
