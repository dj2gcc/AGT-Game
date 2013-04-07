#pragma once 
#include "IdManager.h"
#include "Ogre.h"
#include "Character.h"

class BinPart;

template <class T>

class Event
{
private:

	int _ID;

	Ogre::Vector3* _Position;
	float _Radius;

	T* _Owner;
	void (T::*_Funct) (Character* c);
	

public:

	BinPart* _Part;

	Event(Ogre::Vector3* p, float r,T* owner, void (T::*f)(Character* c))
	{
		_ID = IDManager->newEventID();
		_Position = p;
		_Radius = r;
		_Funct = f;
		_Owner = owner;
	}

	~Event()
	{
	}

	void executeEvent(Character* p)
	{
		(_Owner->_Funct)(p);
	}

	Ogre::Vector3 getPosition() { return *_Position; }
	float getRadius() { return _Radius; }
	int getID() { return _ID; }
};