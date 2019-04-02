// IridiumExecutable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Engine.h"
#include <iostream>
#include <pybind11/embed.h>

#include <Windows.h>

#include <direct.h>


namespace py = pybind11;




int main()
{
	Py_SetProgramName(L"IridiumPython");


	py::initialize_interpreter();

	wchar_t* path = Py_GetPath();

	std::wstring ws(path);
	std::cout << std::string(ws.begin(), ws.end());
	//Todo: Figure out how to properly manager files using Py_SetPath()
	//Py_SetPath()


	if (IridiumEngine::Instance()->Initialize())
		IridiumEngine::Instance()->Run();

	py::finalize_interpreter();

	return 0;
}