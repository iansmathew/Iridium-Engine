#include "PyBehaviour.h"
#include <iostream>
#include "Gameobject.h"


PyBehaviour::PyBehaviour(std::string moduleName ,Gameobject* owner) : BaseComponent(owner)
{
	scriptModule = py::module::import(moduleName.c_str());
}

void PyBehaviour::Start()
{
	scriptModule.attr("Start")(GetGameobject());
}

void PyBehaviour::Update()
{
	scriptModule.attr("Update")();

}

void PyBehaviour::Shutdown()
{
	scriptModule.attr("Shutdown")(GetGameobject());

}


