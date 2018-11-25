#include <memory>
#include "D3DSystem.h"

class IEventData;
typedef std::shared_ptr<IEventData> IEventDataPtr;
typedef std::shared_ptr<D3DSystem> D3DSysPtr;

const bool IS_VSYNC_ENABLED = true;
const bool IS_FULLSCREEN_ENABLED = false;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	bool Initialize(int screenWidth, int screenHeight, HWND HWnd);
	bool Frame();
	bool Render();
	void Shutdown();
	void HandleEvent(IEventDataPtr pEvent);

private:
	D3DSysPtr D3DSys;
	float bgRGBA[4];
};