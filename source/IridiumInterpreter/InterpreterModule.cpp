
#include "irincludes.h"

#include <pybind11/pybind11.h>


namespace py = pybind11;



PYBIND11_MODULE(IridiumPython, m) {
	m.attr("Engine-Name") = "IridiumEngine";


	py::class_<BaseComponent, PyBehaviour> pyBehaviour(m, "PyBehavior");
	pyBehaviour.def(py::init<Gameobject*>());
	//pyBehaviour.def("GetGameObject", &BaseComponent::GetGameobject);
	pyBehaviour.def("Start", &BaseComponent::Start);
	pyBehaviour.def("Update", &BaseComponent::Update);
	pyBehaviour.def("Shutdown", &BaseComponent::Shutdown);
}
