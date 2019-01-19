/**
	BaseSingleton.h

	Purpose: The BaseSingleton class is a generic template class that allows derived classes to
	implement singleton behaviors.

	@author Ian Sebastian Mathew
	@version 1.0 2019-01-09

 */

#pragma once

template <class T>
class BaseSingleton
{
public:
	static T* Instance();
};
