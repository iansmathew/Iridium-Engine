#include "PyBehaviour.h"
#include <iostream>

PyBehaviour::PyBehaviour(Gameobject* owner) : BaseComponent(owner)
{
	std::cout << "Kick Me! \n";
	scriptModule = py::module::import("module1");
}

void PyBehaviour::Start()
{
	scriptModule.attr("Print")();
}

void PyBehaviour::Update()
{

}

void PyBehaviour::Shutdown()
{

}
