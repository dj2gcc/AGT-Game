#include "PlayerController.h"

PlayerController::PlayerController(Character* object) : Controller()
{
		_Up = OIS::KC_W;
		_Down = OIS::KC_S;
		_Left = OIS::KC_A;
		_Right = OIS::KC_D;
		_LeftSide = OIS::KC_Q;
		_RightSide = OIS::KC_E;
		_Jump = OIS::KC_SPACE;

		_Controlled = object;
}

PlayerController::~PlayerController()
{
}

bool PlayerController::setControl(Character* object)
{
	_Controlled = object;
	return true;
}

void PlayerController::keyPressed( const OIS::KeyEvent& evt )
{
	if(evt.key == _Up)
	{
		_Controlled->adjustVelocity(Ogre::Vector3(0, 0, 1));
	}else
		if(evt.key == _Down)
		{
			_Controlled->adjustVelocity(Ogre::Vector3(0, 0, -1));
		}else
			if(evt.key == _Left)
			{
				_Controlled->setRotation(Ogre::Vector3(0, 1, 0));
			}else
				if(evt.key == _Right)
				{
					_Controlled->setRotation(Ogre::Vector3(0, -1, 0));
				}else
					if(evt.key == _LeftSide)
					{
						_Controlled->adjustVelocity(Ogre::Vector3(1, 0, 0));
					}else
						if(evt.key == _RightSide)
						{
							_Controlled->adjustVelocity(Ogre::Vector3(-1, 0, 0));
						}else
							if(evt.key == _Jump)
							{
								_Controlled->Jump();
							}
}

void PlayerController::keyReleased( const OIS::KeyEvent& evt )
{
	if(evt.key == _Up)
	{
		_Controlled->adjustVelocity(Ogre::Vector3(0, 0, -1));
	}else
		if(evt.key == _Down)
		{
			_Controlled->adjustVelocity(Ogre::Vector3(0, 0, 1));
		}else
			if(evt.key == _Left)
			{
				_Controlled->setRotation(Ogre::Vector3(0, 0, 0));
			}else
				if(evt.key == _Right)
				{
					_Controlled->setRotation(Ogre::Vector3(0, 0, 0));
				}else
					if(evt.key == _LeftSide)
					{
						_Controlled->adjustVelocity(Ogre::Vector3(-1, 0, 0));
					}else
						if(evt.key == _RightSide)
						{
							_Controlled->adjustVelocity(Ogre::Vector3(1, 0, 0));
						}
}

void PlayerController::update(Ogre::Real tslf)
{
	_Controlled->update(tslf);
}