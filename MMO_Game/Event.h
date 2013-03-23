#include "Ogre.h"

typedef void (*callback_function)(void);

template <class T>

class Event
{
private:

	Ogre::Vector3 _Position;
	float _Radius;

	callback_function _Function;

public:

	Event(Ogre::Vector3 p, float r)
	{
		_Position = p;
		_Radius = r;
	}

	~Event(){}

	void attachFunction(callback_function f)
	{
		_Function = f;
	}

	void executeEvent(T* p)
	{
		f(p);
	}
};
