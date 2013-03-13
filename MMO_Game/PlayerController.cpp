#include "PlayerController.h"

PlayerController::PlayerController()
{
		_Up = OIS::KC_W;
		_Down = OIS::KC_S;
		_Left = OIS::KC_A;
		_Right = OIS::KC_D;
		_LeftSide = OIS::KC_Q;
		_RightSide = OIS::KC_E;
		_Jump = OIS::KC_SPACE;

		_Controlled = NULL;
}

PlayerController::~PlayerController()
{
}

bool PlayerController::setControl(DynamicObject* object)
{
	_Controlled = object;
	return true;
}

void PlayerController::keyPressed( const OIS::KeyEvent& evt )
{
	if(evt.key == _Up)
	{
	}else
		if(evt.key == _Down)
		{
		}else
			if(evt.key == _Left)
			{
			}else
				if(evt.key == _Right)
				{
				}else
					if(evt.key == _LeftSide)
					{
					}else
						if(evt.key == _RightSide)
						{
						}else
							if(evt.key == _Jump)
							{
							}
}

void PlayerController::keyReleased( const OIS::KeyEvent& evt )
{
	if(evt.key == _Up)
	{
	}else
		if(evt.key == _Down)
		{
		}else
			if(evt.key == _Left)
			{
			}else
				if(evt.key == _Right)
				{
				}else
					if(evt.key == _LeftSide)
					{
					}else
						if(evt.key == _RightSide)
						{
						}
}