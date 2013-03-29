#pragma once 

#include "BinPart.h"
#include "IdManager.h"
#include "Ogre.h"

typedef void (*callback_function)(void);

template <class T>

class Event
{
private:

	int _ID;

	Ogre::Vector3 _Position;
	float _Radius;

	callback_function _Function;

public:

	BinPart* _Part;

public:

	Event(Ogre::Vector3 p, float r)
	{
		_ID = IDManager->newEventID();
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

	Ogre::Vector3 getPosition() { return _Position; }
	float getRadius() { return _Radius; }
	int getID() { return _ID; }
};
