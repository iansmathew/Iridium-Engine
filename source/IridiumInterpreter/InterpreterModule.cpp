
#include "irincludes.h"
#include "pybind11/pybind11.h"
#include <memory>


namespace py = pybind11;


PYBIND11_MODULE(IridiumPython, IridiumModule) {
	py::class_<Gameobject , std::unique_ptr<Gameobject, py::nodelete>>gameobject (IridiumModule, "GameObject");
	gameobject.def_property("Name", &Gameobject::GetName, &Gameobject::SetName);


	py::class_<TrialClass , std::unique_ptr<TrialClass, py::nodelete>> trial(IridiumModule, "SampleClass");
	trial.def_property("Name", &TrialClass::GetString, &TrialClass::SetString);

}