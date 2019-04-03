#include "PyBehaviour.h"
#include <iostream>
#include "Gameobject.h"
#include "MusicComponent.h"



PyBehaviour::PyBehaviour(std::string moduleName ,Gameobject* owner) : BaseComponent(owner)
{
	scriptModule = py::module::import(moduleName.c_str());
	pyObject = scriptModule.attr("PyScriptComponent");
}

void PyBehaviour::Start()
{
	pyObject.attr("Start")(GetGameobject());
	std::cout << GetGameobject()->name;
}

void PyBehaviour::Update()
{
	pyObject.attr("Update")(GetGameobject());

}

void PyBehaviour::Shutdown()
{
	pyObject.attr("Shutdown")(GetGameobject());

}


