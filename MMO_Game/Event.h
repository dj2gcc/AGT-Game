#pragma once 
#include "IdManager.h"
#include "Ogre.h"
#include "Character.h"
#include "AIController.h"

#include "Delegates.h"

class BinPart;

class Event
{
private:

	int _ID;

	Ogre::Vector3* _Position;
	float _Radius;	

	CDelegate1<Character*> _Functor;


public:

	BinPart* _Part;

	Event(Ogre::Vector3* p, float r, CDelegate1<Character*> f)
	{
		_ID = IDManager->newEventID();
		_Position = p;
		_Radius = r;
		_Functor = f;
	}

	~Event()
	{
	}

	void executeEvent(Character* p)
	{
		_Functor(p);
	}

	Ogre::Vector3 getPosition() { return *_Position; }
	float getRadius() { return _Radius; }
	int getID() { return _ID; }
};