// IridiumExecutable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Engine.h"
#include <iostream>


int main()
{
	if (IridiumEngine::Instance()->Initialize())
		IridiumEngine::Instance()->Run();

	return 0;
}