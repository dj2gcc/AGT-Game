#pragma once 
#include "IdManager.h"
#include "Ogre.h"
#include "Character.h"

class BinPart;

class Event
{
private:

	int _ID;

	Ogre::Vector3* _Position;
	float _Radius;	


public:

	BinPart* _Part;

	Event(Ogre::Vector3* p, float r)
	{
		_ID = IDManager->newEventID();
		_Position = p;
		_Radius = r;
	}

	~Event()
	{
	}

	void executeEvent(Character* p)
	{
	}

	Ogre::Vector3 getPosition() { return *_Position; }
	float getRadius() { return _Radius; }
	int getID() { return _ID; }
};