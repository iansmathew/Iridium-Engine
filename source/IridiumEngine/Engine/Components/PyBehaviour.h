#include "BaseComponent.h"

class PyBehaviour :public BaseComponent
{
private:
	

public:
	PyBehaviour(Gameobject* owner);

	virtual void Start() override;
	virtual void Update() override;
	virtual void Shutdown() override;

};

