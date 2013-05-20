#pragma once

#include "OIS.h"
#include "Character.h"

class Controller
{
protected:
		Character* _Controlled;
public:

	virtual void keyPressed( const OIS::KeyEvent& evt ) {};
	virtual void keyReleased( const OIS::KeyEvent& evt ) {};

	virtual bool HandleMessage(Telegram& msg)
	{
		_Controlled->HandleMessage(msg);
		return true;
	}

	Character* getControlled() { return _Controlled; }

	virtual void resetTarget(){}

	virtual void update(Ogre::Real tslf) {};
};