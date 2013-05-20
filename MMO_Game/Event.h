#pragma once 
#include "IdManager.h"
#include "Ogre.h"
#include "Character.h"
#include <delegate/delegate.hpp>

typedef srutil::delegate1<void, Character*> EventDelegate;

class Event
{
private:

	int _ID;

	Character* _Owner;
	float _Radius;	

	EventDelegate _Action;

public:

	Event(Character* p, float r, EventDelegate d, int& id)
	{
		_ID = IDManager->newEventID();
		_Owner = p;
		_Radius = r;
		_Action = d;

		id = _ID;
	}

	~Event()
	{
	}

	void executeEvent(Character* p)
	{
		_Action(p);
	}

	Ogre::Vector3 getPosition() { return _Owner->getPosition(); }
	float getRadius() { return _Radius; }
	int getID() { return _ID; }
};