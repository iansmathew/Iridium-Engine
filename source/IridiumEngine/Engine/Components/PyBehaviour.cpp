#include "PyBehaviour.h"
#include <iostream>


PyBehaviour::PyBehaviour(std::string moduleName ,Gameobject* owner) : BaseComponent(owner)
{
	std::cout << "Kick Me! \n";
	scriptModule = py::module::import(moduleName.c_str());
}

void PyBehaviour::Start()
{
	scriptModule.attr("Start")();
}

void PyBehaviour::Update()
{
	scriptModule.attr("Update")();

}

void PyBehaviour::Shutdown()
{
	scriptModule.attr("Shutdown")();

}
