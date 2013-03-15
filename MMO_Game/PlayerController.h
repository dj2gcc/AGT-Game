#pragma once

#include "OIS.h"
#include "World.h"
#include "Character.h"

class PlayerController : public DynamicObjectDecorator
{
private:

	OIS::KeyCode _Up;
	OIS::KeyCode _Down;
	OIS::KeyCode _Left;
	OIS::KeyCode _Right;
	OIS::KeyCode _LeftSide;
	OIS::KeyCode _RightSide;
	OIS::KeyCode _Jump;

	DynamicObject* _Controlled;

public:

	PlayerController(DynamicObject* object);
	~PlayerController();

	bool setControl(DynamicObject* object);

	void keyPressed( const OIS::KeyEvent& evt );
	void keyReleased( const OIS::KeyEvent& evt );

	void update(Ogre::Real tslf);

	DynamicObject* getControlled() { return _Controlled; }

};