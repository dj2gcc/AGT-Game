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

	Character* getControlled() { return _Controlled; }

	virtual void update(Ogre::Real tslf) {};
};