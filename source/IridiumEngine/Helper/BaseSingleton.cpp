#include "BaseSingleton.h"

/**
	Returns a static instance of the class. The instance is only created the
	first time that Instance() is called.

	@return A pointer to the static instance of <T>.
*/
template <class T>
static T* BaseSingleton<T>::Instance()
{
	static T* inst = new T();
	return inst;
}