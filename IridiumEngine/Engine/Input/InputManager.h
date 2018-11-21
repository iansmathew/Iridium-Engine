
class InputManager
{
public:
	InputManager();
	~InputManager();

	bool Initialize();

	void Shutdown();
	void KeyDown(UINT key);
	void KeyUp(UINT key);

private:

};