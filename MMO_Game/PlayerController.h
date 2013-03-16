#pragma once

#include "Controller.h"

class PlayerController : public Controller
{
private:

	OIS::KeyCode _Up;
	OIS::KeyCode _Down;
	OIS::KeyCode _Left;
	OIS::KeyCode _Right;
	OIS::KeyCode _LeftSide;
	OIS::KeyCode _RightSide;
	OIS::KeyCode _Jump;

public:

	PlayerController(Character* object);
	~PlayerController();

	bool setControl(Character* object);

	void keyPressed( const OIS::KeyEvent& evt );
	void keyReleased( const OIS::KeyEvent& evt );

	void update(Ogre::Real tslf);

};