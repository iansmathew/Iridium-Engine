#include "PyBehaviour.h"
#include <iostream>

PyBehaviour::PyBehaviour(Gameobject* owner) : BaseComponent(owner)
{
	std::cout << "Kick Me! \n";
	scriptModule = py::module::import("pysample");
}

void PyBehaviour::Start()
{
	scriptModule.attr("Call")();
}

void PyBehaviour::Update()
{

}

void PyBehaviour::Shutdown()
{

}
