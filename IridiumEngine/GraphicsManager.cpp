#include "stdafx.h"
#include "Engine/Graphics/GraphicsManager.h"
#include "Engine/Event/EventManager.h"
#include "Engine/Event/Events.h"

GraphicsManager::GraphicsManager()
{
	D3DSys = nullptr;
}

GraphicsManager::~GraphicsManager()
{

}

bool GraphicsManager::Initialize(int screenWidth, int screenHeight, HWND HWnd)
{
	//TODO: Remove unwanted event queuing

	//EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate(this, &GraphicsManager::HandleEvent);
	//EventManager::Get()->AddListener(delegateFunc, EvtData_On_Key_Event::eventType);

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
	D3DSys->BeginScene(0.5f, 0.5f, 0.5f, 1.0f); //Gray

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

	//std::shared_ptr<EvtData_On_Key_Event> pCastEventData = std::static_pointer_cast<EvtData_On_Key_Event>(pEventData);

	//char* x = new char(pCastEventData->GetKeyValue());
	//OutputDebugStringA(x);
}
