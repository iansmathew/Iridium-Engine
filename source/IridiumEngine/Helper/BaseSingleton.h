/**
	BaseSingleton.h

	Purpose: The BaseSingleton class is a generic template class that allows derived classes to
	implement singleton behaviors. This loosely follows the CRTP: https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern

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

template <class T>
T* BaseSingleton<T>::Instance()
{
	static T* inst = new T();
	return inst;
}
