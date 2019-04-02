#include <pybind11/pybind11.h>

#include "BaseComponent.h"

namespace py = pybind11;


class PyBehaviour : public BaseComponent
{
public:
	PyBehaviour(Gameobject* owner);

	void Start() override;
	void Update() override;
	void Shutdown() override;
	~PyBehaviour() =  default;

private:

	py::module scriptModule;

};