#include <memory>
class IEventData;
typedef std::shared_ptr<IEventData> IEventDataPtr;

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	bool Initialize(int screenWidth, int screenHeight, HWND HWnd);
	bool Frame();
	void Shutdown();
	void HandleEvent(IEventDataPtr pEvent);
};