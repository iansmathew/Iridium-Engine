#include <pybind11/pybind11.h>
#include <string>
#include "BaseComponent.h"
#include <bitset>
#include "Gameobject.h"

namespace py = pybind11;


class PyBehaviour : public BaseComponent
{
public:
	PyBehaviour(std::string moduleName , Gameobject* owner);

	void Start() override;
	void Update() override;
	void Shutdown() override;

private:

	py::module scriptModule;

};


class TrialClass
{


using ComponentsExistBitset = std::bitset<maxComponents>;
using ComponentPointerArray = std::array<BaseComponent*, maxComponents>;
public:
	std::string sampleText;

	std::string GetString() {
		return sampleText;
	}

	void SetString(std::string string) {
		sampleText = string;
	}

};