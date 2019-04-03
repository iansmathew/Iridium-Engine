#pragma once
#include "Engine/Components/BaseComponent.h"
#include "pybind11/pybind11.h"

class PyComponent: public BaseComponent
{

public:
	using BaseComponent::BaseComponent;

	void Start() override { PYBIND11_OVERLOAD_PURE(void, BaseComponent, Start); }
	
	void Update() override { PYBIND11_OVERLOAD_PURE(void, BaseComponent, Update); }
	
	void Shutdown() override { PYBIND11_OVERLOAD_PURE(void, BaseComponent, Shutdown); }
};

