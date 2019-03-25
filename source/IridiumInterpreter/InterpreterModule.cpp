
#include "irincludes.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

class Base
{
public:
	Base() = default;

	virtual int Start() = 0;


	~Base() = default;
	

private:

};


class Derived : public Base
{
public:
	Derived() = default;

	int Start() override {
		PYBIND11_OVERLOAD_PURE(int, Base, Start);
	}

	~Derived() = default;


private:

};

PYBIND11_MODULE(IridiumEngine, m) {
	m.attr("Engine-Name") = "IridiumEngine";
	
	py::class_<Derived, Base>(m, "PyBehaviour")
		.def(py::init<>())
		.def("Start", &Base::Start);

	
}
