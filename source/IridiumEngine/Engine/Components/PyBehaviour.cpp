#include "PyBehaviour.h"
#include <pybind11/pybind11.h>

PyBehaviour::PyBehaviour(Gameobject* owner) : BaseComponent(owner) {

}

void PyBehaviour::Start	(){
	PYBIND11_OVERLOAD_PURE(
		void, /* Return type */
		BaseComponent,      /* Parent class */
		Start,          /* Name of function in C++ (must match Python name) */
	);

}

void PyBehaviour::Update() {
	PYBIND11_OVERLOAD_PURE(
		void,	 /* Return type */
		BaseComponent,      /* Parent class */
		Update,          /* Name of function in C++ (must match Python name) */
		);

}

void PyBehaviour::Shutdown() {
	PYBIND11_OVERLOAD_PURE(
		void, /* Return type */
		BaseComponent,      /* Parent class */
		Shutdown,          /* Name of function in C++ (must match Python name) */
		);

}