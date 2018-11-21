
class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	bool Initialize(int screenWidth, int screenHeight, HWND HWnd);
	bool Frame();
	void Shutdown();
};