/**
	Engine.h
	Purpose: Defines the main Iridium engine class  and methods.

	@author Ian Sebastian Mathew
	@version 1.0 2019-01-19
 */

#pragma once

class IridiumEngine
{
private:
	int instanceValues = 0;

public:
	static IridiumEngine* Instance();

public:
	~IridiumEngine();

private:
	IridiumEngine();
	IridiumEngine(const IridiumEngine &_copy) = delete; //no copy constructor

	bool Initialize();

};